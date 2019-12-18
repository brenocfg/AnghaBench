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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ iMagic; int nPinned; int nFree; scalar_t__ bPurgeable; TYPE_1__* a; int /*<<< orphan*/  szExtra; int /*<<< orphan*/  szPage; } ;
typedef  TYPE_2__ testpcache ;
struct TYPE_9__ {int /*<<< orphan*/  pExtra; int /*<<< orphan*/  pBuf; } ;
typedef  TYPE_3__ sqlite3_pcache_page ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_10__ {scalar_t__ pDummy; scalar_t__ nInstance; scalar_t__ highStress; } ;
struct TYPE_7__ {unsigned int key; int isPinned; TYPE_3__ page; } ;

/* Variables and functions */
 int TESTPCACHE_NPAGE ; 
 int TESTPCACHE_RESERVE ; 
 scalar_t__ TESTPCACHE_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ testpcacheGlobal ; 
 int testpcacheRandom (TYPE_2__*) ; 

__attribute__((used)) static sqlite3_pcache_page *testpcacheFetch(
  sqlite3_pcache *pCache,
  unsigned key,
  int createFlag
){
  testpcache *p = (testpcache*)pCache;
  int i, j;
  assert( p->iMagic==TESTPCACHE_VALID );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance>0 );

  /* See if the page is already in cache.  Return immediately if it is */
  for(i=0; i<TESTPCACHE_NPAGE; i++){
    if( p->a[i].key==key ){
      if( !p->a[i].isPinned ){
        p->nPinned++;
        assert( p->nPinned <= TESTPCACHE_NPAGE - p->nFree );
        p->a[i].isPinned = 1;
      }
      return &p->a[i].page;
    }
  }

  /* If createFlag is 0, never allocate a new page */
  if( createFlag==0 ){
    return 0;
  }

  /* If no pages are available, always fail */
  if( p->nPinned==TESTPCACHE_NPAGE ){
    return 0;
  }

  /* Do not allocate the last TESTPCACHE_RESERVE pages unless createFlag is 2 */
  if( p->nPinned>=TESTPCACHE_NPAGE-TESTPCACHE_RESERVE && createFlag<2 ){
    return 0;
  }

  /* Do not allocate if highStress is enabled and createFlag is not 2.  
  **
  ** The highStress setting causes pagerStress() to be called much more
  ** often, which exercises the pager logic more intensely.
  */
  if( testpcacheGlobal.highStress && createFlag<2 ){
    return 0;
  }

  /* Find a free page to allocate if there are any free pages.
  ** Withhold TESTPCACHE_RESERVE free pages until createFlag is 2.
  */
  if( p->nFree>TESTPCACHE_RESERVE || (createFlag==2 && p->nFree>0) ){
    j = testpcacheRandom(p) % TESTPCACHE_NPAGE;
    for(i=0; i<TESTPCACHE_NPAGE; i++, j = (j+1)%TESTPCACHE_NPAGE){
      if( p->a[j].key==0 ){
        p->a[j].key = key;
        p->a[j].isPinned = 1;
        memset(p->a[j].page.pBuf, 0, p->szPage);
        memset(p->a[j].page.pExtra, 0, p->szExtra);
        p->nPinned++;
        p->nFree--;
        assert( p->nPinned <= TESTPCACHE_NPAGE - p->nFree );
        return &p->a[j].page;
      }
    }

    /* The prior loop always finds a freepage to allocate */
    assert( 0 );
  }

  /* If this cache is not purgeable then we have to fail.
  */
  if( p->bPurgeable==0 ){
    return 0;
  }

  /* If there are no free pages, recycle a page.  The page to
  ** recycle is selected at random from all unpinned pages.
  */
  j = testpcacheRandom(p) % TESTPCACHE_NPAGE;
  for(i=0; i<TESTPCACHE_NPAGE; i++, j = (j+1)%TESTPCACHE_NPAGE){
    if( p->a[j].key>0 && p->a[j].isPinned==0 ){
      p->a[j].key = key;
      p->a[j].isPinned = 1;
      memset(p->a[j].page.pBuf, 0, p->szPage);
      memset(p->a[j].page.pExtra, 0, p->szExtra);
      p->nPinned++;
      assert( p->nPinned <= TESTPCACHE_NPAGE - p->nFree );
      return &p->a[j].page;
    }
  }

  /* The previous loop always finds a page to recycle. */
  assert(0);
  return 0;
}