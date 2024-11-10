#pragma once

#include "common/type/data_type.h"
using date = unsigned;
/**
 * @brief 日期类型
 * @ingroup DataType
 */
class NullType : public DataType
{
public:
  NullType() : DataType(AttrType::INTS) {}
  virtual ~NullType() {}

  int compare(const Value &left, const Value &right) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  RC to_string(const Value &val, string &result) const override;
};