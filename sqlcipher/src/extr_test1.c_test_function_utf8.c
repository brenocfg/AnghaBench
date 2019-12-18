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
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetStringResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ValueNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ValueSetStr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text16be (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text16be (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_function_utf8(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **argv
){
  Tcl_Interp *interp;
  Tcl_Obj *pX;
  sqlite3_value *pVal;
  interp = (Tcl_Interp *)sqlite3_user_data(pCtx);
  pX = Tcl_NewStringObj("test_function", -1);
  Tcl_IncrRefCount(pX);
  Tcl_ListObjAppendElement(interp, pX, Tcl_NewStringObj("UTF-8", -1));
  Tcl_ListObjAppendElement(interp, pX, 
      Tcl_NewStringObj((char*)sqlite3_value_text(argv[0]), -1));
  Tcl_EvalObjEx(interp, pX, 0);
  Tcl_DecrRefCount(pX);
  sqlite3_result_text(pCtx, Tcl_GetStringResult(interp), -1, SQLITE_TRANSIENT);
  pVal = sqlite3ValueNew(0);
  sqlite3ValueSetStr(pVal, -1, Tcl_GetStringResult(interp), 
      SQLITE_UTF8, SQLITE_STATIC);
  sqlite3_result_text16be(pCtx, sqlite3_value_text16be(pVal),
      -1, SQLITE_TRANSIENT);
  sqlite3ValueFree(pVal);
}