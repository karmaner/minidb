#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<FieldMeta> fields)
  :table_(table)
  ,values_(values)
  ,fields_(fields) { }