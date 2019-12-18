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
struct TYPE_8__ {int /*<<< orphan*/  (* xUnpin ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_11__ {TYPE_1__ pcache2; } ;
struct TYPE_10__ {int nRef; int flags; int /*<<< orphan*/  pPage; TYPE_2__* pCache; } ;
struct TYPE_9__ {int /*<<< orphan*/  pCache; int /*<<< orphan*/  nRefSum; } ;
typedef  TYPE_3__ PgHdr ;

/* Variables and functions */
 int /*<<< orphan*/  PCACHE_DIRTYLIST_REMOVE ; 
 int PGHDR_DIRTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcacheManageDirtyList (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_6__ sqlite3GlobalConfig ; 
 int sqlite3PcachePageSanity (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void sqlite3PcacheDrop(PgHdr *p){
  assert( p->nRef==1 );
  assert( sqlite3PcachePageSanity(p) );
  if( p->flags&PGHDR_DIRTY ){
    pcacheManageDirtyList(p, PCACHE_DIRTYLIST_REMOVE);
  }
  p->pCache->nRefSum--;
  sqlite3GlobalConfig.pcache2.xUnpin(p->pCache->pCache, p->pPage, 1);
}