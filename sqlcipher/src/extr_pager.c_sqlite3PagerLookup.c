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
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
struct TYPE_3__ {scalar_t__ pPCache; scalar_t__ hasHeldSharedLock; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ Pager ;
typedef  int /*<<< orphan*/  DbPage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3PcacheFetch (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3PcacheFetchFinish (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

DbPage *sqlite3PagerLookup(Pager *pPager, Pgno pgno){
  sqlite3_pcache_page *pPage;
  assert( pPager!=0 );
  assert( pgno!=0 );
  assert( pPager->pPCache!=0 );
  pPage = sqlite3PcacheFetch(pPager->pPCache, pgno, 0);
  assert( pPage==0 || pPager->hasHeldSharedLock );
  if( pPage==0 ) return 0;
  return sqlite3PcacheFetchFinish(pPager->pPCache, pgno, pPage);
}