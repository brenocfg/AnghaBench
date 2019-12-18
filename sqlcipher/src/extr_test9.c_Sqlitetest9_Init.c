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
typedef  int /*<<< orphan*/  aObjCmd ;
typedef  int /*<<< orphan*/  Tcl_ObjCmdProc ;
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_CreateObjCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
#define  c_collation_test 130 
#define  c_misuse_test 129 
#define  c_realloc_test 128 

int Sqlitetest9_Init(Tcl_Interp *interp){
  static struct {
     char *zName;
     Tcl_ObjCmdProc *xProc;
     void *clientData;
  } aObjCmd[] = {
     { "c_misuse_test",    c_misuse_test, 0 },
     { "c_realloc_test",   c_realloc_test, 0 },
     { "c_collation_test", c_collation_test, 0 },
  };
  int i;
  for(i=0; i<sizeof(aObjCmd)/sizeof(aObjCmd[0]); i++){
    Tcl_CreateObjCommand(interp, aObjCmd[i].zName, 
        aObjCmd[i].xProc, aObjCmd[i].clientData, 0);
  }
  return TCL_OK;
}