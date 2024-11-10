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
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"

int CharType::compare(const Value &left, const Value &right) const
{
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case AttrType::BOOLEANS :{
      result.set_boolean(bool(val.get_date() == 0));
      return rc;
    } break;
    case AttrType::DATES :{
      result.set_date(date(val.get_date()));
      return rc;
    } break;
    case AttrType::FLOATS :{
      result.set_float(val.get_float());
      return rc;
    } break;
    case AttrType::INTS :{
      result.set_int(val.get_date());
      return rc;
    } break;
    default: {
      LOG_WARN("undefine cast_to type type=", attr_type_to_string(type));
      return RC::UNIMPLEMENTED;
    }
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type != AttrType::CHARS) {
    return 0;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}