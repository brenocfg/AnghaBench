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
typedef  int /*<<< orphan*/  Fts3Cursor ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_value_pointer (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int fts3FunctionArg(
  sqlite3_context *pContext,      /* SQL function call context */
  const char *zFunc,              /* Function name */
  sqlite3_value *pVal,            /* argv[0] passed to function */
  Fts3Cursor **ppCsr              /* OUT: Store cursor handle here */
){
  int rc;
  *ppCsr = (Fts3Cursor*)sqlite3_value_pointer(pVal, "fts3cursor");
  if( (*ppCsr)!=0 ){
    rc = SQLITE_OK;
  }else{
    char *zErr = sqlite3_mprintf("illegal first argument to %s", zFunc);
    sqlite3_result_error(pContext, zErr, -1);
    sqlite3_free(zErr);
    rc = SQLITE_ERROR;
  }
  return rc;
}