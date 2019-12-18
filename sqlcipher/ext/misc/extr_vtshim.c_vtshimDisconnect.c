#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pNext; TYPE_1__** ppPrev; int /*<<< orphan*/  pChild; TYPE_4__* pAux; } ;
typedef  TYPE_3__ vtshim_vtab ;
struct TYPE_9__ {TYPE_2__* pMod; int /*<<< orphan*/  bDisposed; } ;
typedef  TYPE_4__ vtshim_aux ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int (* xDisconnect ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {struct TYPE_6__** ppPrev; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtshimDisconnect(sqlite3_vtab *pBase){
  vtshim_vtab *pVtab = (vtshim_vtab*)pBase;
  vtshim_aux *pAux = pVtab->pAux;
  int rc = SQLITE_OK;
  if( !pAux->bDisposed ){
    rc = pAux->pMod->xDisconnect(pVtab->pChild);
  }
  if( pVtab->pNext ) pVtab->pNext->ppPrev = pVtab->ppPrev;
  *pVtab->ppPrev = pVtab->pNext;
  sqlite3_free(pVtab);
  return rc;
}