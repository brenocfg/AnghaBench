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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int TCL_OK ; 
 scalar_t__ sqlite3TestTextToPtr (char const*) ; 

__attribute__((used)) static int getStmtPointer(
  Tcl_Interp *interp, 
  const char *zArg,  
  sqlite3_stmt **ppStmt
){
  *ppStmt = (sqlite3_stmt*)sqlite3TestTextToPtr(zArg);
  return TCL_OK;
}