#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nMapLimit; TYPE_1__* pLruLast; TYPE_1__* pLruFirst; } ;
struct TYPE_6__ {scalar_t__ nRef; int flags; int /*<<< orphan*/  iPg; struct TYPE_6__* pLruPrev; struct TYPE_6__* pLruNext; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ FileSystem ;

/* Variables and functions */
 int PAGE_FREE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* fsPageFindInHash (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_lists_are_ok(FileSystem *pFS){
#if 0
  Page *p;

  assert( pFS->nMapLimit>=0 );

  /* Check that all pages in the LRU list have nRef==0, pointers to buffers
  ** in heap memory, and corresponding entries in the hash table.  */
  for(p=pFS->pLruFirst; p; p=p->pLruNext){
    assert( p==pFS->pLruFirst || p->pLruPrev!=0 );
    assert( p==pFS->pLruLast || p->pLruNext!=0 );
    assert( p->pLruPrev==0 || p->pLruPrev->pLruNext==p );
    assert( p->pLruNext==0 || p->pLruNext->pLruPrev==p );
    assert( p->nRef==0 );
    assert( p->flags & PAGE_FREE );
    assert( p==fsPageFindInHash(pFS, p->iPg, 0) );
  }
#endif
}