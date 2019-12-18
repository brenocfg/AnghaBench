#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  pBuf; } ;
typedef  TYPE_2__ sqlite3_pcache_page ;
struct TYPE_10__ {int /*<<< orphan*/  (* xTruncate ) (scalar_t__,int) ;TYPE_2__* (* xFetch ) (scalar_t__,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_1__ pcache2; } ;
struct TYPE_13__ {scalar_t__ pCache; int /*<<< orphan*/  szPage; scalar_t__ nRefSum; TYPE_3__* pDirty; } ;
struct TYPE_12__ {scalar_t__ pgno; int flags; struct TYPE_12__* pDirtyNext; } ;
typedef  int Pgno ;
typedef  TYPE_3__ PgHdr ;
typedef  TYPE_4__ PCache ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_2__*) ; 
 int PGHDR_DIRTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_8__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3PcacheMakeClean (TYPE_3__*) ; 
 TYPE_2__* stub1 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int) ; 

void sqlite3PcacheTruncate(PCache *pCache, Pgno pgno){
  if( pCache->pCache ){
    PgHdr *p;
    PgHdr *pNext;
    pcacheTrace(("%p.TRUNCATE %d\n",pCache,pgno));
    for(p=pCache->pDirty; p; p=pNext){
      pNext = p->pDirtyNext;
      /* This routine never gets call with a positive pgno except right
      ** after sqlite3PcacheCleanAll().  So if there are dirty pages,
      ** it must be that pgno==0.
      */
      assert( p->pgno>0 );
      if( p->pgno>pgno ){
        assert( p->flags&PGHDR_DIRTY );
        sqlite3PcacheMakeClean(p);
      }
    }
    if( pgno==0 && pCache->nRefSum ){
      sqlite3_pcache_page *pPage1;
      pPage1 = sqlite3GlobalConfig.pcache2.xFetch(pCache->pCache,1,0);
      if( ALWAYS(pPage1) ){  /* Page 1 is always available in cache, because
                             ** pCache->nRefSum>0 */
        memset(pPage1->pBuf, 0, pCache->szPage);
        pgno = 1;
      }
    }
    sqlite3GlobalConfig.pcache2.xTruncate(pCache->pCache, pgno+1);
  }
}