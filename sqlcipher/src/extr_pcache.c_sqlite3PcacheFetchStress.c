#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
struct TYPE_10__ {int /*<<< orphan*/ * (* xFetch ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* xPagecount ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_1__ pcache2; } ;
struct TYPE_12__ {int eCreate; scalar_t__ szSpill; int (* xStress ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  pCache; int /*<<< orphan*/  pStress; TYPE_2__* pDirtyTail; TYPE_2__* pSynced; } ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  pgno; struct TYPE_11__* pDirtyPrev; scalar_t__ nRef; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ PgHdr ;
typedef  TYPE_3__ PCache ;

/* Variables and functions */
 int PGHDR_NEED_SYNC ; 
 int SQLITE_BUSY ; 
 int /*<<< orphan*/  SQLITE_FULL ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  numberOfCachePages (TYPE_3__*) ; 
 int /*<<< orphan*/  pcacheDump (TYPE_3__*) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_7__ sqlite3GlobalConfig ; 
 scalar_t__ sqlite3PcachePagecount (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int sqlite3PcacheFetchStress(
  PCache *pCache,                 /* Obtain the page from this cache */
  Pgno pgno,                      /* Page number to obtain */
  sqlite3_pcache_page **ppPage    /* Write result here */
){
  PgHdr *pPg;
  if( pCache->eCreate==2 ) return 0;

  if( sqlite3PcachePagecount(pCache)>pCache->szSpill ){
    /* Find a dirty page to write-out and recycle. First try to find a 
    ** page that does not require a journal-sync (one with PGHDR_NEED_SYNC
    ** cleared), but if that is not possible settle for any other 
    ** unreferenced dirty page.
    **
    ** If the LRU page in the dirty list that has a clear PGHDR_NEED_SYNC
    ** flag is currently referenced, then the following may leave pSynced
    ** set incorrectly (pointing to other than the LRU page with NEED_SYNC
    ** cleared). This is Ok, as pSynced is just an optimization.  */
    for(pPg=pCache->pSynced; 
        pPg && (pPg->nRef || (pPg->flags&PGHDR_NEED_SYNC)); 
        pPg=pPg->pDirtyPrev
    );
    pCache->pSynced = pPg;
    if( !pPg ){
      for(pPg=pCache->pDirtyTail; pPg && pPg->nRef; pPg=pPg->pDirtyPrev);
    }
    if( pPg ){
      int rc;
#ifdef SQLITE_LOG_CACHE_SPILL
      sqlite3_log(SQLITE_FULL, 
                  "spill page %d making room for %d - cache used: %d/%d",
                  pPg->pgno, pgno,
                  sqlite3GlobalConfig.pcache2.xPagecount(pCache->pCache),
                numberOfCachePages(pCache));
#endif
      pcacheTrace(("%p.SPILL %d\n",pCache,pPg->pgno));
      rc = pCache->xStress(pCache->pStress, pPg);
      pcacheDump(pCache);
      if( rc!=SQLITE_OK && rc!=SQLITE_BUSY ){
        return rc;
      }
    }
  }
  *ppPage = sqlite3GlobalConfig.pcache2.xFetch(pCache->pCache, pgno, 2);
  return *ppPage==0 ? SQLITE_NOMEM_BKPT : SQLITE_OK;
}