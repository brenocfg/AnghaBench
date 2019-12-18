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
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int SQLITE_PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
#define  SQLITE_UTF16BE 130 
#define  SQLITE_UTF16LE 129 
#define  SQLITE_UTF8 128 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetIntFromObj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pTestCollateInterp ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3ValueFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3ValueNew (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ValueSetStr (int /*<<< orphan*/ *,int,void const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_collate_func(
  void *pCtx, 
  int nA, const void *zA,
  int nB, const void *zB
){
  Tcl_Interp *i = pTestCollateInterp;
  int encin = SQLITE_PTR_TO_INT(pCtx);
  int res;
  int n;

  sqlite3_value *pVal;
  Tcl_Obj *pX;

  pX = Tcl_NewStringObj("test_collate", -1);
  Tcl_IncrRefCount(pX);

  switch( encin ){
    case SQLITE_UTF8:
      Tcl_ListObjAppendElement(i,pX,Tcl_NewStringObj("UTF-8",-1));
      break;
    case SQLITE_UTF16LE:
      Tcl_ListObjAppendElement(i,pX,Tcl_NewStringObj("UTF-16LE",-1));
      break;
    case SQLITE_UTF16BE:
      Tcl_ListObjAppendElement(i,pX,Tcl_NewStringObj("UTF-16BE",-1));
      break;
    default:
      assert(0);
  }

  sqlite3BeginBenignMalloc();
  pVal = sqlite3ValueNew(0);
  if( pVal ){
    sqlite3ValueSetStr(pVal, nA, zA, encin, SQLITE_STATIC);
    n = sqlite3_value_bytes(pVal);
    Tcl_ListObjAppendElement(i,pX,
        Tcl_NewStringObj((char*)sqlite3_value_text(pVal),n));
    sqlite3ValueSetStr(pVal, nB, zB, encin, SQLITE_STATIC);
    n = sqlite3_value_bytes(pVal);
    Tcl_ListObjAppendElement(i,pX,
        Tcl_NewStringObj((char*)sqlite3_value_text(pVal),n));
    sqlite3ValueFree(pVal);
  }
  sqlite3EndBenignMalloc();

  Tcl_EvalObjEx(i, pX, 0);
  Tcl_DecrRefCount(pX);
  Tcl_GetIntFromObj(i, Tcl_GetObjResult(i), &res);
  return res;
}