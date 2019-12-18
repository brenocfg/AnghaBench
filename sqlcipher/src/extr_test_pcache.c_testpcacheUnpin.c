#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ iMagic; scalar_t__ nPinned; int nFree; TYPE_1__* a; scalar_t__ bPurgeable; } ;
typedef  TYPE_2__ testpcache ;
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_7__ {scalar_t__ pDummy; scalar_t__ nInstance; int discardChance; } ;
struct TYPE_5__ {int isPinned; scalar_t__ key; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int TESTPCACHE_NPAGE ; 
 scalar_t__ TESTPCACHE_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ testpcacheGlobal ; 
 int testpcacheRandom (TYPE_2__*) ; 

__attribute__((used)) static void testpcacheUnpin(
  sqlite3_pcache *pCache,
  sqlite3_pcache_page *pOldPage,
  int discard
){
  testpcache *p = (testpcache*)pCache;
  int i;
  assert( p->iMagic==TESTPCACHE_VALID );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance>0 );

  /* Randomly discard pages as they are unpinned according to the
  ** discardChance setting.  If discardChance is 0, the random discard
  ** never happens.  If discardChance is 100, it always happens.
  */
  if( p->bPurgeable
  && (100-testpcacheGlobal.discardChance) <= (testpcacheRandom(p)%100)
  ){
    discard = 1;
  }

  for(i=0; i<TESTPCACHE_NPAGE; i++){
    if( &p->a[i].page==pOldPage ){
      /* The pOldPage pointer always points to a pinned page */
      assert( p->a[i].isPinned );
      p->a[i].isPinned = 0;
      p->nPinned--;
      assert( p->nPinned>=0 );
      if( discard ){
        p->a[i].key = 0;
        p->nFree++;
        assert( p->nFree<=TESTPCACHE_NPAGE );
      }
      return;
    }
  }

  /* The pOldPage pointer always points to a valid page */
  assert( 0 );
}