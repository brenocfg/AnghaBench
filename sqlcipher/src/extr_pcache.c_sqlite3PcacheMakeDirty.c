#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nRef; int flags; int /*<<< orphan*/  pgno; int /*<<< orphan*/  pCache; } ;
typedef  TYPE_1__ PgHdr ;

/* Variables and functions */
 int /*<<< orphan*/  PCACHE_DIRTYLIST_ADD ; 
 int PGHDR_CLEAN ; 
 int PGHDR_DIRTY ; 
 int PGHDR_DONT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcacheManageDirtyList (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 int sqlite3PcachePageSanity (TYPE_1__*) ; 

void sqlite3PcacheMakeDirty(PgHdr *p){
  assert( p->nRef>0 );
  assert( sqlite3PcachePageSanity(p) );
  if( p->flags & (PGHDR_CLEAN|PGHDR_DONT_WRITE) ){    /*OPTIMIZATION-IF-FALSE*/
    p->flags &= ~PGHDR_DONT_WRITE;
    if( p->flags & PGHDR_CLEAN ){
      p->flags ^= (PGHDR_DIRTY|PGHDR_CLEAN);
      pcacheTrace(("%p.DIRTY %d\n",p->pCache,p->pgno));
      assert( (p->flags & (PGHDR_DIRTY|PGHDR_CLEAN))==PGHDR_DIRTY );
      pcacheManageDirtyList(p, PCACHE_DIRTYLIST_ADD);
    }
    assert( sqlite3PcachePageSanity(p) );
  }
}