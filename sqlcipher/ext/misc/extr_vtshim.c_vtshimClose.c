#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_6__* pAux; } ;
typedef  TYPE_4__ vtshim_vtab ;
struct TYPE_10__ {scalar_t__ pVtab; } ;
struct TYPE_12__ {TYPE_2__* pNext; TYPE_2__** ppPrev; int /*<<< orphan*/  pChild; TYPE_3__ base; } ;
typedef  TYPE_5__ vtshim_cursor ;
struct TYPE_13__ {TYPE_1__* pMod; int /*<<< orphan*/  bDisposed; } ;
typedef  TYPE_6__ vtshim_aux ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_9__ {struct TYPE_9__** ppPrev; } ;
struct TYPE_8__ {int (* xClose ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  VTSHIM_COPY_ERRMSG () ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_5__*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtshimClose(sqlite3_vtab_cursor *pX){
  vtshim_cursor *pCur = (vtshim_cursor*)pX;
  vtshim_vtab *pVtab = (vtshim_vtab*)pCur->base.pVtab;
  vtshim_aux *pAux = pVtab->pAux;
  int rc = SQLITE_OK;
  if( !pAux->bDisposed ){
    rc = pAux->pMod->xClose(pCur->pChild);
    if( rc!=SQLITE_OK ){
      VTSHIM_COPY_ERRMSG();
    }
  }
  if( pCur->pNext ) pCur->pNext->ppPrev = pCur->ppPrev;
  *pCur->ppPrev = pCur->pNext;
  sqlite3_free(pCur);
  return rc;
}