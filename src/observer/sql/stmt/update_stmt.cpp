#include "sql/stmt/update_stmt.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount, FilterStmt* filter_stmt, FieldMeta* field_meta)
    : table_(table)
    ,values_(values)
    ,value_amount_(value_amount)
    ,filter_stmt_(filter_stmt)
    ,field_meta_(field_meta)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{

  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  const char* table_name = update.relation_name.c_str();
  Table* table = db->find_table(table_name);
  if(!table) {
    LOG_WARN("no such table table_name=%s", table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<string, Table*> table_map;
  table_map.insert({table_name, table});

  const FieldMeta* field_meta = table->table_meta().field(update.attribute_name.c_str());
  if(nullptr == field_meta) {
    LOG_WARN("no such field in table. db=%s, table=%s, field name=%s", db->name(), table_name, update.attribute_name.c_str());
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  FilterStmt* filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);

  Value value = update.value;

  stmt = new UpdateStmt(table, &value, 1, filter_stmt, const_cast<FieldMeta*>(field_meta));

  return rc;
}
