#pragma once

#include "sql/stmt/stmt.h"

class Db;
class Table;
class FilterStmt;
class FieldMeta;

/**
 * @brief 更新语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt() = default;
  UpdateStmt(Table *table, Value *values, int value_amount, FilterStmt* filter_stmt, FieldMeta* field_meta);

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

public:
  Table *table() const { return table_; }
  Value *values() const { return values_; }
  FilterStmt*                 filter_stmt() { return filter_stmt_; }
  FieldMeta*                  field_meta() { return field_meta_; }
  int    value_amount() const { return value_amount_; }

private:
  Table *table_               = nullptr;
  Value *values_              = nullptr;
  int    value_amount_        = 0;
  FilterStmt* filter_stmt_    = nullptr;
  FieldMeta*  field_meta_     = nullptr;
};
