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
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_CreateObjCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_circle_geom ; 
 int /*<<< orphan*/  register_cube_geom ; 

int Sqlitetestrtree_Init(Tcl_Interp *interp){
  Tcl_CreateObjCommand(interp, "register_cube_geom", register_cube_geom, 0, 0);
  Tcl_CreateObjCommand(interp, "register_circle_geom",register_circle_geom,0,0);
  return TCL_OK;
}