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
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int SQLITE_MISUSE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  Tcl_AppendResult (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ResetResult (int /*<<< orphan*/ *) ; 
 int sqlite3_errcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_threadsafe () ; 
 int /*<<< orphan*/  t1ErrorName (int) ; 

int sqlite3TestErrCode(Tcl_Interp *interp, sqlite3 *db, int rc){
  if( sqlite3_threadsafe()==0 && rc!=SQLITE_MISUSE && rc!=SQLITE_OK
   && sqlite3_errcode(db)!=rc ){
    char zBuf[200];
    int r2 = sqlite3_errcode(db);
    sqlite3_snprintf(sizeof(zBuf), zBuf,
       "error code %s (%d) does not match sqlite3_errcode %s (%d)",
       t1ErrorName(rc), rc, t1ErrorName(r2), r2);
    Tcl_ResetResult(interp);
    Tcl_AppendResult(interp, zBuf, 0);
    return 1;
  }
  return 0;
}