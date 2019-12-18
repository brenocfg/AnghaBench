#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ iMagic; scalar_t__ nPinned; unsigned int nFree; TYPE_1__* a; } ;
typedef  TYPE_2__ testpcache ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_6__ {scalar_t__ pDummy; scalar_t__ nInstance; } ;
struct TYPE_4__ {unsigned int key; scalar_t__ isPinned; } ;

/* Variables and functions */
 unsigned int TESTPCACHE_NPAGE ; 
 scalar_t__ TESTPCACHE_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ testpcacheGlobal ; 

__attribute__((used)) static void testpcacheTruncate(sqlite3_pcache *pCache, unsigned iLimit){
  testpcache *p = (testpcache*)pCache;
  unsigned int i;
  assert( p->iMagic==TESTPCACHE_VALID );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance>0 );
  for(i=0; i<TESTPCACHE_NPAGE; i++){
    if( p->a[i].key>=iLimit ){
      p->a[i].key = 0;
      if( p->a[i].isPinned ){
        p->nPinned--;
        assert( p->nPinned>=0 );
      }
      p->nFree++;
      assert( p->nFree<=TESTPCACHE_NPAGE );
    }
  }
}