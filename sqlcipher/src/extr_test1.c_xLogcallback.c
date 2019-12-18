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
typedef  int /*<<< orphan*/  Tcl_Obj ;
struct TYPE_2__ {int /*<<< orphan*/  pInterp; int /*<<< orphan*/  pObj; } ;

/* Variables and functions */
 int TCL_EVAL_DIRECT ; 
 int TCL_EVAL_GLOBAL ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_DuplicateObj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_EvalObjEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_NewStringObj (char*,int) ; 
 TYPE_1__ logcallback ; 
 char* sqlite3ErrName (int) ; 

__attribute__((used)) static void xLogcallback(void *unused, int err, char *zMsg){
  Tcl_Obj *pNew = Tcl_DuplicateObj(logcallback.pObj);
  Tcl_IncrRefCount(pNew);
  Tcl_ListObjAppendElement(
      0, pNew, Tcl_NewStringObj(sqlite3ErrName(err), -1)
  );
  Tcl_ListObjAppendElement(0, pNew, Tcl_NewStringObj(zMsg, -1));
  Tcl_EvalObjEx(logcallback.pInterp, pNew, TCL_EVAL_GLOBAL|TCL_EVAL_DIRECT);
  Tcl_DecrRefCount(pNew);
}