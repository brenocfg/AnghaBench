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
 int /*<<< orphan*/  testAsyncControl ; 
 int /*<<< orphan*/  testAsyncInit ; 
 int /*<<< orphan*/  testAsyncShutdown ; 
 int /*<<< orphan*/  testAsyncStart ; 
 int /*<<< orphan*/  testAsyncWait ; 

int Sqlitetestasync_Init(Tcl_Interp *interp){
#ifdef SQLITE_ENABLE_ASYNCIO
  Tcl_CreateObjCommand(interp,"sqlite3async_start",testAsyncStart,0,0);
  Tcl_CreateObjCommand(interp,"sqlite3async_wait",testAsyncWait,0,0);

  Tcl_CreateObjCommand(interp,"sqlite3async_control",testAsyncControl,0,0);
  Tcl_CreateObjCommand(interp,"sqlite3async_initialize",testAsyncInit,0,0);
  Tcl_CreateObjCommand(interp,"sqlite3async_shutdown",testAsyncShutdown,0,0);
#endif  /* SQLITE_ENABLE_ASYNCIO */
  return TCL_OK;
}