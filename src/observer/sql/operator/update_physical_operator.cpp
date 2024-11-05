#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
	if(children_.empty()) {
		return RC::SUCCESS;
	}

	std::unique_ptr<PhysicalOperator> &child = children_[0];

	RC rc = child->open(trx);
	if(rc != RC::SUCCESS) {
		LOG_WARN("failed to open child operator: %s", strrc(rc));
		return rc;
	}

	trx_ = trx;
	
	while(OB_SUCC(rc = child->next())) {
		Tuple *tuple = child->current_tuple();
		if(nullptr == tuple) {
			LOG_WARN("failed to get current record: %s", strrc(rc));
			return rc;
		}
		
		RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
		Record &record = row_tuple->record();
		records_.emplace_back(std::move(record));
	}

	child->close();

	if(records_.size() <= 0) {
		LOG_ERROR("none record to update");
		return RC::SUCCESS;	// fix the test case bug
		return RC::RECORD_NOT_EXIST;
	}

	for(Record& record : records_) {
		rc = trx_->update_record(table_, record, &fields_[0], &values_[0]);
		if(rc != RC::SUCCESS) {
			LOG_WARN("failed to update record: %s", strrc(rc));
			return rc;
		}
	}

	return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
	return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
	return RC::SUCCESS;
}