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
typedef  int /*<<< orphan*/  Tcl_ThreadCreateType ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
struct TYPE_3__ {char* zVarname; int /*<<< orphan*/  zScript; } ;
typedef  TYPE_1__ SqlThread ;
typedef  void* ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  Sqlite3_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Sqlitetest1_Init (int /*<<< orphan*/ *) ; 
 int TCL_ALL_EVENTS ; 
 int TCL_DONT_WAIT ; 
 int TCL_OK ; 
 int /*<<< orphan*/  TCL_THREAD_CREATE_RETURN ; 
 int /*<<< orphan*/ * Tcl_CreateInterp () ; 
 int /*<<< orphan*/  Tcl_CreateObjCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_DeleteInterp (int /*<<< orphan*/ *) ; 
 scalar_t__ Tcl_DoOneEvent (int) ; 
 int Tcl_Eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ExitThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Tcl_GetObjResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_IncrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Tcl_ListObjAppendElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Tcl_NewObj () ; 
 int /*<<< orphan*/ * Tcl_NewStringObj (char*,int) ; 
 int /*<<< orphan*/  blocking_prepare_v2_proc ; 
 int /*<<< orphan*/  blocking_step_proc ; 
 int /*<<< orphan*/  ckfree (void*) ; 
 int /*<<< orphan*/  clock_seconds_proc ; 
 int /*<<< orphan*/  postToParent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlthread_proc ; 

__attribute__((used)) static Tcl_ThreadCreateType tclScriptThread(ClientData pSqlThread){
  Tcl_Interp *interp;
  Tcl_Obj *pRes;
  Tcl_Obj *pList;
  int rc;
  SqlThread *p = (SqlThread *)pSqlThread;
  extern int Sqlitetest_mutex_Init(Tcl_Interp*);

  interp = Tcl_CreateInterp();
  Tcl_CreateObjCommand(interp, "clock_seconds", clock_seconds_proc, 0, 0);
  Tcl_CreateObjCommand(interp, "sqlthread", sqlthread_proc, pSqlThread, 0);
#if SQLITE_OS_UNIX && defined(SQLITE_ENABLE_UNLOCK_NOTIFY)
  Tcl_CreateObjCommand(interp, "sqlite3_blocking_step", blocking_step_proc,0,0);
  Tcl_CreateObjCommand(interp, 
      "sqlite3_blocking_prepare_v2", blocking_prepare_v2_proc, (void *)1, 0);
  Tcl_CreateObjCommand(interp, 
      "sqlite3_nonblocking_prepare_v2", blocking_prepare_v2_proc, 0, 0);
#endif
  Sqlitetest1_Init(interp);
  Sqlitetest_mutex_Init(interp);
  Sqlite3_Init(interp);

  rc = Tcl_Eval(interp, p->zScript);
  pRes = Tcl_GetObjResult(interp);
  pList = Tcl_NewObj();
  Tcl_IncrRefCount(pList);
  Tcl_IncrRefCount(pRes);

  if( rc!=TCL_OK ){
    Tcl_ListObjAppendElement(interp, pList, Tcl_NewStringObj("error", -1));
    Tcl_ListObjAppendElement(interp, pList, pRes);
    postToParent(p, pList);
    Tcl_DecrRefCount(pList);
    pList = Tcl_NewObj();
  }

  Tcl_ListObjAppendElement(interp, pList, Tcl_NewStringObj("set", -1));
  Tcl_ListObjAppendElement(interp, pList, Tcl_NewStringObj(p->zVarname, -1));
  Tcl_ListObjAppendElement(interp, pList, pRes);
  postToParent(p, pList);

  ckfree((void *)p);
  Tcl_DecrRefCount(pList);
  Tcl_DecrRefCount(pRes);
  Tcl_DeleteInterp(interp);
  while( Tcl_DoOneEvent(TCL_ALL_EVENTS|TCL_DONT_WAIT) );
  Tcl_ExitThread(0);
  TCL_THREAD_CREATE_RETURN;
}