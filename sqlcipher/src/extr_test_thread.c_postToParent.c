#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Event ;
struct TYPE_5__ {int /*<<< orphan*/  proc; scalar_t__ nextPtr; } ;
struct TYPE_7__ {char* zScript; int /*<<< orphan*/  interp; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  interp; } ;
typedef  TYPE_2__ SqlThread ;
typedef  TYPE_3__ EvalEvent ;

/* Variables and functions */
 int /*<<< orphan*/  TCL_QUEUE_TAIL ; 
 char* Tcl_GetStringFromObj (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  Tcl_ThreadAlert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_ThreadQueueEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ckalloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  tclScriptEvent ; 

__attribute__((used)) static void postToParent(SqlThread *p, Tcl_Obj *pScript){
  EvalEvent *pEvent;
  char *zMsg;
  int nMsg;

  zMsg = Tcl_GetStringFromObj(pScript, &nMsg); 
  pEvent = (EvalEvent *)ckalloc(sizeof(EvalEvent)+nMsg+1);
  pEvent->base.nextPtr = 0;
  pEvent->base.proc = tclScriptEvent;
  pEvent->zScript = (char *)&pEvent[1];
  memcpy(pEvent->zScript, zMsg, nMsg+1);
  pEvent->interp = p->interp;

  Tcl_ThreadQueueEvent(p->parent, (Tcl_Event *)pEvent, TCL_QUEUE_TAIL);
  Tcl_ThreadAlert(p->parent);
}