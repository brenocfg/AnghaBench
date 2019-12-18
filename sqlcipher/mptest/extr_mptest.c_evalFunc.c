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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_5__ {int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ String ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  evalCallback ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stringFree (TYPE_1__*) ; 

__attribute__((used)) static void evalFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  sqlite3 *db = sqlite3_context_db_handle(context);
  const char *zSql = (const char*)sqlite3_value_text(argv[0]);
  String res;
  char *zErrMsg = 0;
  int rc;
  UNUSED_PARAMETER(argc);
  memset(&res, 0, sizeof(res));
  rc = sqlite3_exec(db, zSql, evalCallback, &res, &zErrMsg);
  if( zErrMsg ){
    sqlite3_result_error(context, zErrMsg, -1);
    sqlite3_free(zErrMsg);
  }else if( rc ){
    sqlite3_result_error_code(context, rc);
  }else{
    sqlite3_result_text(context, res.z, -1, SQLITE_TRANSIENT);
  }
  stringFree(&res);
}