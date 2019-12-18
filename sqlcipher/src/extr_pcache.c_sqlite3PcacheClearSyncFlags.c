#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pDirtyTail; int /*<<< orphan*/  pSynced; TYPE_1__* pDirty; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; struct TYPE_4__* pDirtyNext; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ PCache ;

/* Variables and functions */
 int /*<<< orphan*/  PGHDR_NEED_SYNC ; 

void sqlite3PcacheClearSyncFlags(PCache *pCache){
  PgHdr *p;
  for(p=pCache->pDirty; p; p=p->pDirtyNext){
    p->flags &= ~PGHDR_NEED_SYNC;
  }
  pCache->pSynced = pCache->pDirtyTail;
}