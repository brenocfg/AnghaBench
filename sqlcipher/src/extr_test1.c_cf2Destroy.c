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
struct TYPE_3__ {scalar_t__ pDestroy; scalar_t__ pFinal; scalar_t__ pStep; scalar_t__ pFunc; scalar_t__ interp; } ;
typedef  TYPE_1__ CreateFunctionV2 ;

/* Variables and functions */
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_BackgroundError (scalar_t__) ; 
 int /*<<< orphan*/  Tcl_DecrRefCount (scalar_t__) ; 
 int Tcl_EvalObjEx (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void cf2Destroy(void *pUser){
  CreateFunctionV2 *p = (CreateFunctionV2 *)pUser;

  if( p->interp && p->pDestroy ){
    int rc = Tcl_EvalObjEx(p->interp, p->pDestroy, 0);
    if( rc!=TCL_OK ) Tcl_BackgroundError(p->interp);
  }

  if( p->pFunc ) Tcl_DecrRefCount(p->pFunc); 
  if( p->pStep ) Tcl_DecrRefCount(p->pStep); 
  if( p->pFinal ) Tcl_DecrRefCount(p->pFinal); 
  if( p->pDestroy ) Tcl_DecrRefCount(p->pDestroy); 
  sqlite3_free(p);
}