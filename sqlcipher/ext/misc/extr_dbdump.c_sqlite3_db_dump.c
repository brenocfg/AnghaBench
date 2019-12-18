#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int rc; int (* xCallback ) (char const*,void*) ;scalar_t__ nErr; scalar_t__ writableSchema; void* pArg; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ DState ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_sql_from_query (TYPE_1__*,char*,char const*,...) ; 
 int /*<<< orphan*/  run_schema_dump_query (TYPE_1__*,char*,char const*,...) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3_db_dump(
  sqlite3 *db,               /* The database connection */
  const char *zSchema,       /* Which schema to dump.  Usually "main". */
  const char *zTable,        /* Which table to dump.  NULL means everything. */
  int (*xCallback)(const char*,void*),   /* Output sent to this callback */
  void *pArg                             /* Second argument of the callback */
){
  DState x;
  memset(&x, 0, sizeof(x));
  x.rc = sqlite3_exec(db, "BEGIN", 0, 0, 0);
  if( x.rc ) return x.rc;
  x.db = db;
  x.xCallback = xCallback;
  x.pArg = pArg;
  xCallback("PRAGMA foreign_keys=OFF;\nBEGIN TRANSACTION;\n", pArg);
  if( zTable==0 ){
    run_schema_dump_query(&x,
      "SELECT name, type, sql FROM \"%w\".sqlite_master "
      "WHERE sql NOT NULL AND type=='table' AND name!='sqlite_sequence'",
      zSchema
    );
    run_schema_dump_query(&x,
      "SELECT name, type, sql FROM \"%w\".sqlite_master "
      "WHERE name=='sqlite_sequence'", zSchema
    );
    output_sql_from_query(&x,
      "SELECT sql FROM sqlite_master "
      "WHERE sql NOT NULL AND type IN ('index','trigger','view')", 0
    );
  }else{
    run_schema_dump_query(&x,
      "SELECT name, type, sql FROM \"%w\".sqlite_master "
      "WHERE tbl_name=%Q COLLATE nocase AND type=='table'"
      "  AND sql NOT NULL",
      zSchema, zTable
    );
    output_sql_from_query(&x,
      "SELECT sql FROM \"%w\".sqlite_master "
      "WHERE sql NOT NULL"
      "  AND type IN ('index','trigger','view')"
      "  AND tbl_name=%Q COLLATE nocase",
      zSchema, zTable
    ); 
  }
  if( x.writableSchema ){
    xCallback("PRAGMA writable_schema=OFF;\n", pArg);
  }
  xCallback(x.nErr ? "ROLLBACK; -- due to errors\n" : "COMMIT;\n", pArg);
  sqlite3_exec(db, "COMMIT", 0, 0, 0);
  return x.rc;
}