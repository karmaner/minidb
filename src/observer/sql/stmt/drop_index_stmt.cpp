#include "sql/stmt/drop_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"


RC DropIndexStmt::create(Db *db, const DropIndexSqlNode &drop_index, Stmt *&stmt) {
  // TODO: 实现drop index
  return RC::SUCCESS;
}


