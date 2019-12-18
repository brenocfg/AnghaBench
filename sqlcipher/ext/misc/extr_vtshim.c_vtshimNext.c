#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* pAux; } ;
typedef  TYPE_3__ vtshim_vtab ;
struct TYPE_6__ {scalar_t__ pVtab; } ;
struct TYPE_9__ {int /*<<< orphan*/  pChild; TYPE_1__ base; } ;
typedef  TYPE_4__ vtshim_cursor ;
struct TYPE_10__ {TYPE_2__* pMod; scalar_t__ bDisposed; } ;
typedef  TYPE_5__ vtshim_aux ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_7__ {int (* xNext ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  VTSHIM_COPY_ERRMSG () ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtshimNext(sqlite3_vtab_cursor *pX){
  vtshim_cursor *pCur = (vtshim_cursor*)pX;
  vtshim_vtab *pVtab = (vtshim_vtab*)pCur->base.pVtab;
  vtshim_aux *pAux = pVtab->pAux;
  int rc;
  if( pAux->bDisposed ) return SQLITE_ERROR;
  rc = pAux->pMod->xNext(pCur->pChild);
  if( rc!=SQLITE_OK ){
    VTSHIM_COPY_ERRMSG();
  }
  return rc;
}