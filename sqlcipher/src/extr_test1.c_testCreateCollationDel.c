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
struct TYPE_2__ {int /*<<< orphan*/  pDel; int /*<<< orphan*/  pCmp; int /*<<< orphan*/  interp; } ;
typedef  TYPE_1__ TestCollationX ;

/* Variables and functions */
 int TCL_EVAL_DIRECT ; 
 int TCL_EVAL_GLOBAL ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_BackgroundError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ ) ; 
 int Tcl_EvalObjEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 

__attribute__((used)) static void testCreateCollationDel(void *pCtx){
  TestCollationX *p = (TestCollationX *)pCtx;

  int rc = Tcl_EvalObjEx(p->interp, p->pDel, TCL_EVAL_DIRECT|TCL_EVAL_GLOBAL);
  if( rc!=TCL_OK ){
    Tcl_BackgroundError(p->interp);
  }

  Tcl_DecrRefCount(p->pCmp);
  Tcl_DecrRefCount(p->pDel);
  sqlite3_free((void *)p);
}