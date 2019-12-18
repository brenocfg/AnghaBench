#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* xRekey ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_1__ pcache2; } ;
struct TYPE_10__ {int /*<<< orphan*/  pCache; } ;
struct TYPE_9__ {scalar_t__ nRef; int flags; int /*<<< orphan*/  pgno; int /*<<< orphan*/  pPage; TYPE_3__* pCache; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ PgHdr ;
typedef  TYPE_3__ PCache ;

/* Variables and functions */
 int /*<<< orphan*/  PCACHE_DIRTYLIST_FRONT ; 
 int PGHDR_DIRTY ; 
 int PGHDR_NEED_SYNC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcacheManageDirtyList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_6__ sqlite3GlobalConfig ; 
 int sqlite3PcachePageSanity (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sqlite3PcacheMove(PgHdr *p, Pgno newPgno){
  PCache *pCache = p->pCache;
  assert( p->nRef>0 );
  assert( newPgno>0 );
  assert( sqlite3PcachePageSanity(p) );
  pcacheTrace(("%p.MOVE %d -> %d\n",pCache,p->pgno,newPgno));
  sqlite3GlobalConfig.pcache2.xRekey(pCache->pCache, p->pPage, p->pgno,newPgno);
  p->pgno = newPgno;
  if( (p->flags&PGHDR_DIRTY) && (p->flags&PGHDR_NEED_SYNC) ){
    pcacheManageDirtyList(p, PCACHE_DIRTYLIST_FRONT);
  }
}