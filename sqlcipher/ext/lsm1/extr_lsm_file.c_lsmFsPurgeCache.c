#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ nCacheAlloc; scalar_t__ nOut; scalar_t__ pLruLast; TYPE_1__* pLruFirst; } ;
struct TYPE_7__ {int flags; struct TYPE_7__* pLruNext; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int PAGE_FREE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fsPageBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  fsPageRemoveFromHash (TYPE_2__*,TYPE_1__*) ; 

void lsmFsPurgeCache(FileSystem *pFS){
  Page *pPg;

  pPg = pFS->pLruFirst;
  while( pPg ){
    Page *pNext = pPg->pLruNext;
    assert( pPg->flags & PAGE_FREE );
    fsPageRemoveFromHash(pFS, pPg);
    fsPageBufferFree(pPg);
    pPg = pNext;
  }
  pFS->pLruFirst = 0;
  pFS->pLruLast = 0;

  assert( pFS->nCacheAlloc<=pFS->nOut && pFS->nCacheAlloc>=0 );
}