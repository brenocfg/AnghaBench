#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * pnPurgeable; TYPE_3__* pFree; TYPE_2__* pGroup; } ;
struct TYPE_7__ {int /*<<< orphan*/  pBuf; } ;
struct TYPE_9__ {TYPE_1__ page; struct TYPE_9__* pNext; scalar_t__ isBulkLocal; TYPE_4__* pCache; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_3__ PgHdr1 ;
typedef  TYPE_4__ PCache1 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcache1Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcache1FreePage(PgHdr1 *p){
  PCache1 *pCache;
  assert( p!=0 );
  pCache = p->pCache;
  assert( sqlite3_mutex_held(p->pCache->pGroup->mutex) );
  if( p->isBulkLocal ){
    p->pNext = pCache->pFree;
    pCache->pFree = p;
  }else{
    pcache1Free(p->page.pBuf);
#ifdef SQLITE_PCACHE_SEPARATE_HEADER
    sqlite3_free(p);
#endif
  }
  (*pCache->pnPurgeable)--;
}