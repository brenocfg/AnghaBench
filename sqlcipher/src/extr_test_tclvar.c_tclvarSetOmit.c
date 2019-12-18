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
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int TCL_OK ; 
 int Tcl_Eval (int /*<<< orphan*/ *,char*) ; 
 int Tcl_GetBooleanFromObj (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * Tcl_GetObjResult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tclvarSetOmit(Tcl_Interp *interp){
  int rc;
  int res = 0;
  Tcl_Obj *pRes;
  rc = Tcl_Eval(interp,
    "expr {[info exists ::tclvar_set_omit] && $::tclvar_set_omit}"
  );
  if( rc==TCL_OK ){
    pRes = Tcl_GetObjResult(interp);
    rc = Tcl_GetBooleanFromObj(0, pRes, &res);
  }
  return (rc==TCL_OK && res);
}