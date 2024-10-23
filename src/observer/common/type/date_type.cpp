/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/date_type.h"
#include "common/value.h"

int DateType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::DATES, "left type is not dates");
  ASSERT(right.attr_type() == AttrType::DATES, "right type is not dates");
    return common::compare_date((void *)&left, (void *)&right);
}

RC DateType::add(const Value &left, const Value &right, Value &result) const
{
	// TODO: 日期加减
  result.set_date(left.get_date() + right.get_int());
  return RC::SUCCESS;
}

RC DateType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_date(left.get_date() - right.get_int());
  return RC::SUCCESS;
}


RC DateType::set_value_from_str(Value &val, const string &data) const
{
  RC                rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();  // 清理stream的状态，防止多次解析出现异常
  deserialize_stream.str(data);
  date date_value;
	int year, month, day;
	char c;
  deserialize_stream >> year >> c >> month >> c >> day;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
		date_value = year * 10000 + month * 100 + day;
    val.set_date(date_value);
  }
  return rc;
}

RC DateType::to_string(const Value &val, string &result) const
{
  stringstream ss;
	unsigned  date_value = val.value_.int_value_;
	unsigned	year = date_value / 10000;
	unsigned	month = (date_value / 100) % 100;
	unsigned	day = date_value % 100;

	ss << year << '-' 
			<< (month < 10 ? "0" : "") << month << '-' 
			<< (day < 10 ? "0" : "") << day;
  result = ss.str();
  return RC::SUCCESS;
}