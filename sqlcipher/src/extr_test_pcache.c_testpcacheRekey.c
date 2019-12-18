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
struct TYPE_5__ {scalar_t__ iMagic; int nFree; TYPE_1__* a; } ;
typedef  TYPE_2__ testpcache ;
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_6__ {scalar_t__ pDummy; scalar_t__ nInstance; } ;
struct TYPE_4__ {unsigned int key; int isPinned; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int TESTPCACHE_NPAGE ; 
 scalar_t__ TESTPCACHE_VALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ testpcacheGlobal ; 

__attribute__((used)) static void testpcacheRekey(
  sqlite3_pcache *pCache,
  sqlite3_pcache_page *pOldPage,
  unsigned oldKey,
  unsigned newKey
){
  testpcache *p = (testpcache*)pCache;
  int i;
  assert( p->iMagic==TESTPCACHE_VALID );
  assert( testpcacheGlobal.pDummy!=0 );
  assert( testpcacheGlobal.nInstance>0 );

  /* If there already exists another page at newKey, verify that
  ** the other page is unpinned and discard it.
  */
  for(i=0; i<TESTPCACHE_NPAGE; i++){
    if( p->a[i].key==newKey ){
      /* The new key is never a page that is already pinned */
      assert( p->a[i].isPinned==0 );
      p->a[i].key = 0;
      p->nFree++;
      assert( p->nFree<=TESTPCACHE_NPAGE );
      break;
    }
  }

  /* Find the page to be rekeyed and rekey it.
  */
  for(i=0; i<TESTPCACHE_NPAGE; i++){
    if( p->a[i].key==oldKey ){
      /* The oldKey and pOldPage parameters match */
      assert( &p->a[i].page==pOldPage );
      /* Page to be rekeyed must be pinned */
      assert( p->a[i].isPinned );
      p->a[i].key = newKey;
      return;
    }
  }

  /* Rekey is always given a valid page to work with */
  assert( 0 );
}