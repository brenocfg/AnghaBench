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
typedef  int /*<<< orphan*/  x ;
struct EvalResult {char* zSep; int szSep; char* z; scalar_t__ nUsed; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/  memset (struct EvalResult*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct EvalResult*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/  (*) (char*)) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void sqlEvalFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const char *zSql;
  sqlite3 *db;
  char *zErr = 0;
  int rc;
  struct EvalResult x;

  memset(&x, 0, sizeof(x));
  x.zSep = " ";
  zSql = (const char*)sqlite3_value_text(argv[0]);
  if( zSql==0 ) return;
  if( argc>1 ){
    x.zSep = (const char*)sqlite3_value_text(argv[1]);
    if( x.zSep==0 ) return;
  }
  x.szSep = (int)strlen(x.zSep);
  db = sqlite3_context_db_handle(context);
  rc = sqlite3_exec(db, zSql, callback, &x, &zErr);
  if( rc!=SQLITE_OK ){
    sqlite3_result_error(context, zErr, -1);
    sqlite3_free(zErr);
  }else if( x.zSep==0 ){
    sqlite3_result_error_nomem(context);
    sqlite3_free(x.z);
  }else{
    sqlite3_result_text(context, x.z, (int)x.nUsed, sqlite3_free);
  }
}