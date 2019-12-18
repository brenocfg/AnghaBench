#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ i2; int /*<<< orphan*/ * pList2; } ;
typedef  TYPE_1__ tclvar_cursor ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int /*<<< orphan*/  TCL_EVAL_GLOBAL ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjLength (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int next2(Tcl_Interp *interp, tclvar_cursor *pCur, Tcl_Obj *pObj){
  Tcl_Obj *p;

  if( pObj ){
    if( !pCur->pList2 ){
      p = Tcl_NewStringObj("array names", -1);
      Tcl_IncrRefCount(p);
      Tcl_ListObjAppendElement(0, p, pObj);
      Tcl_EvalObjEx(interp, p, TCL_EVAL_GLOBAL);
      Tcl_DecrRefCount(p);
      pCur->pList2 = Tcl_GetObjResult(interp);
      Tcl_IncrRefCount(pCur->pList2);
      assert( pCur->i2==0 );
    }else{
      int n = 0;
      pCur->i2++;
      Tcl_ListObjLength(0, pCur->pList2, &n);
      if( pCur->i2>=n ){
        Tcl_DecrRefCount(pCur->pList2);
        pCur->pList2 = 0;
        pCur->i2 = 0;
        return 0;
      }
    }
  }

  return 1;
}