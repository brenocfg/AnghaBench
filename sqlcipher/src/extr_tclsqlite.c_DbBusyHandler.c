#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zVal ;
struct TYPE_2__ {int /*<<< orphan*/  interp; int /*<<< orphan*/  zBusy; } ;
typedef  TYPE_1__ SqliteDb ;

/* Variables and functions */
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_GetStringResult (int /*<<< orphan*/ ) ; 
 int Tcl_VarEval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 

__attribute__((used)) static int DbBusyHandler(void *cd, int nTries){
  SqliteDb *pDb = (SqliteDb*)cd;
  int rc;
  char zVal[30];

  sqlite3_snprintf(sizeof(zVal), zVal, "%d", nTries);
  rc = Tcl_VarEval(pDb->interp, pDb->zBusy, " ", zVal, (char*)0);
  if( rc!=TCL_OK || atoi(Tcl_GetStringResult(pDb->interp)) ){
    return 0;
  }
  return 1;
}