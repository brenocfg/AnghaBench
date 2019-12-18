#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pFree; TYPE_1__* pMapped; scalar_t__ pCompress; int /*<<< orphan*/  nOut; } ;
struct TYPE_8__ {scalar_t__ nRef; int flags; int aData; struct TYPE_8__* pFreeNext; struct TYPE_8__* pMappedNext; int /*<<< orphan*/  iPg; TYPE_2__* pFS; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int PAGE_FREE ; 
 int PAGE_HASPREV ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fsIsFirst (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsPageAddToLru (TYPE_2__*,TYPE_1__*) ; 
 int lsmFsPagePersist (TYPE_1__*) ; 

int lsmFsPageRelease(Page *pPg){
  int rc = LSM_OK;
  if( pPg ){
    assert( pPg->nRef>0 );
    pPg->nRef--;
    if( pPg->nRef==0 ){
      FileSystem *pFS = pPg->pFS;
      rc = lsmFsPagePersist(pPg);
      pFS->nOut--;

      assert( pPg->pFS->pCompress 
           || fsIsFirst(pPg->pFS, pPg->iPg)==0 
           || (pPg->flags & PAGE_HASPREV)
      );
      pPg->aData -= (pPg->flags & PAGE_HASPREV);
      pPg->flags &= ~PAGE_HASPREV;

      if( (pPg->flags & PAGE_FREE)==0 ){
        /* Removed from mapped list */
        Page **pp;
        for(pp=&pFS->pMapped; (*pp)!=pPg; pp=&(*pp)->pMappedNext);
        *pp = pPg->pMappedNext;
        pPg->pMappedNext = 0;

        /* Add to free list */
        pPg->pFreeNext = pFS->pFree;
        pFS->pFree = pPg;
      }else{
        fsPageAddToLru(pFS, pPg);
      }
    }
  }

  return rc;
}