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
struct TYPE_2__ {int /*<<< orphan*/  interp; int /*<<< orphan*/  pCmp; } ;
typedef  TYPE_1__ TestCollationX ;
typedef  int /*<<< orphan*/  Tcl_Obj ;

/* Variables and functions */
 int TCL_EVAL_DIRECT ; 
 int TCL_EVAL_GLOBAL ; 
 scalar_t__ TCL_OK ; 
 int /*<<< orphan*/  Tcl_BackgroundError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_DuplicateObj (int /*<<< orphan*/ ) ; 
 scalar_t__ Tcl_EvalObjEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Tcl_GetIntFromObj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Tcl_GetObjResult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 

__attribute__((used)) static int testCreateCollationCmp(
  void *pCtx,
  int nLeft,
  const void *zLeft,
  int nRight,
  const void *zRight
){
  TestCollationX *p = (TestCollationX *)pCtx;
  Tcl_Obj *pScript = Tcl_DuplicateObj(p->pCmp);
  int iRes = 0;

  Tcl_IncrRefCount(pScript);
  Tcl_ListObjAppendElement(0, pScript, Tcl_NewStringObj((char *)zLeft, nLeft));
  Tcl_ListObjAppendElement(0, pScript, Tcl_NewStringObj((char *)zRight,nRight));

  if( TCL_OK!=Tcl_EvalObjEx(p->interp, pScript, TCL_EVAL_DIRECT|TCL_EVAL_GLOBAL)
   || TCL_OK!=Tcl_GetIntFromObj(p->interp, Tcl_GetObjResult(p->interp), &iRes)
  ){
    Tcl_BackgroundError(p->interp);
  }
  Tcl_DecrRefCount(pScript);

  return iRes;
}