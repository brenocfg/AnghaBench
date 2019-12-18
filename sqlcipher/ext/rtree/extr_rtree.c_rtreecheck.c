#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int rtreeCheckTable (int /*<<< orphan*/ ,char const*,char const*,char**) ; 
 int /*<<< orphan*/  sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtreecheck(
  sqlite3_context *ctx, 
  int nArg, 
  sqlite3_value **apArg
){
  if( nArg!=1 && nArg!=2 ){
    sqlite3_result_error(ctx, 
        "wrong number of arguments to function rtreecheck()", -1
    );
  }else{
    int rc;
    char *zReport = 0;
    const char *zDb = (const char*)sqlite3_value_text(apArg[0]);
    const char *zTab;
    if( nArg==1 ){
      zTab = zDb;
      zDb = "main";
    }else{
      zTab = (const char*)sqlite3_value_text(apArg[1]);
    }
    rc = rtreeCheckTable(sqlite3_context_db_handle(ctx), zDb, zTab, &zReport);
    if( rc==SQLITE_OK ){
      sqlite3_result_text(ctx, zReport ? zReport : "ok", -1, SQLITE_TRANSIENT);
    }else{
      sqlite3_result_error_code(ctx, rc);
    }
    sqlite3_free(zReport);
  }
}