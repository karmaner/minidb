#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/null_type.h"
#include "common/value.h"

int NullType::compare(const Value &left, const Value &right) const
{
  if (left.is_null() && right.is_null()) {
      return 0; // 两个都是 NULL，视为相等
  }
  // 根据 SQL NULL 比较规则，不直接比较 NULL
  LOG_WARN("Attempting to compare NULL values in SQL logic.");
  return INT32_MAX;
}


RC NullType::set_value_from_str(Value &val, const string &data) const
{
  if (data == "NULL" || data.empty()) {
      val.set_null();
      return RC::SUCCESS;
  } else {
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }
}

RC NullType::to_string(const Value &val, string &result) const
{
  result = "NULL";
  return RC::SUCCESS;
}