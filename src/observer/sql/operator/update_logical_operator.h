#pragma once

#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<Value> values, std::vector<FieldMeta> fields);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

public:
  Table                  *table() const { return table_; }
  std::vector<Value>     &values() { return values_; }
  std::vector<FieldMeta> &fields() { return fields_; }

  // 插入逻辑算子需要表格名称以及插入的值以及插入域
private:
  Table            *table_ = nullptr;
  vector<Value>     values_;
  vector<FieldMeta> fields_;
};