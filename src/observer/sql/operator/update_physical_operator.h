#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class DeleteStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, vector<Value> values, vector<FieldMeta> fields) : table_(table), values_(values) , fields_(fields) {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table              *table_ = nullptr;
  Trx                *trx_   = nullptr;
  std::vector<Record> records_;
  vector<Value>     values_;
  vector<FieldMeta> fields_;
};
