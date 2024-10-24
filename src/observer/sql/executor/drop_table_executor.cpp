#include <memory>

#include "sql/executor/drop_table_executor.h"

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/operator/string_list_physical_operator.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
  RC            rc            = RC::SUCCESS;
  Stmt         *stmt          = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session      *session       = session_event->session();
  ASSERT(stmt->type() == StmtType::DROP_TABLE,
      "drop table executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);
  SqlResult     *sql_result      = session_event->sql_result();
  const char    *table_name      = drop_table_stmt->table_name().c_str();

  Db    *db    = session->get_current_db();
  Table *table = db->find_table(table_name);
  
  // TODO: 下面的代码需要修改
  if (table != nullptr) {
    rc = db->drop_table(table_name);
  } else {

    sql_result->set_return_code(RC::SCHEMA_TABLE_NOT_EXIST);
    sql_result->set_state_string("Table not exists");
  }
  return rc;         
}