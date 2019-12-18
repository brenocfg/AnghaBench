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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int checkFreelist (int /*<<< orphan*/ *,char const*,char**) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void checkfreelist_function(
  sqlite3_context *pCtx,
  int nArg,
  sqlite3_value **apArg
){
  const char *zDb;
  int rc;
  char *zOut = 0;
  sqlite3 *db = sqlite3_context_db_handle(pCtx);

  assert( nArg==1 );
  zDb = (const char*)sqlite3_value_text(apArg[0]);
  rc = checkFreelist(db, zDb, &zOut);
  if( rc==SQLITE_OK ){
    sqlite3_result_text(pCtx, zOut?zOut:"ok", -1, SQLITE_TRANSIENT);
  }else{
    sqlite3_result_error_code(pCtx, rc);
  }

  sqlite3_free(zOut);
}