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
struct buffer_head {scalar_t__ b_bcb; TYPE_2__* b_mdl; } ;
struct TYPE_5__ {int /*<<< orphan*/  MappedSystemVa; int /*<<< orphan*/  MdlFlags; } ;
struct TYPE_4__ {int /*<<< orphan*/  bh_count; int /*<<< orphan*/  bh_cache; } ;
typedef  int ERESOURCE_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  CcUnpinDataForThread (scalar_t__,int) ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEC_MEM_COUNT (int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  DL_BH ; 
 int /*<<< orphan*/  Ext2DestroyMdl (TYPE_2__*) ; 
 scalar_t__ IsFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDL_MAPPED_TO_SYSTEM_VA ; 
 int /*<<< orphan*/  MmUnmapLockedPages (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PS_BUFF_HEAD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 TYPE_1__ g_jbh ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct buffer_head*) ; 

void
free_buffer_head(struct buffer_head * bh)
{
    if (bh) {
        if (bh->b_mdl) {

            DEBUG(DL_BH, ("bh=%p mdl=%p (Flags:%xh VA:%p) released.\n", bh, bh->b_mdl,
                          bh->b_mdl->MdlFlags, bh->b_mdl->MappedSystemVa));
            if (IsFlagOn(bh->b_mdl->MdlFlags, MDL_MAPPED_TO_SYSTEM_VA)) {
                MmUnmapLockedPages(bh->b_mdl->MappedSystemVa, bh->b_mdl);
            }
            Ext2DestroyMdl(bh->b_mdl);
        }
        if (bh->b_bcb) {
            CcUnpinDataForThread(bh->b_bcb, (ERESOURCE_THREAD)bh | 0x3);
        }

        DEBUG(DL_BH, ("bh=%p freed.\n", bh));
        DEC_MEM_COUNT(PS_BUFF_HEAD, bh, sizeof(struct buffer_head));
        kmem_cache_free(g_jbh.bh_cache, bh);
        atomic_dec(&g_jbh.bh_count);
    }
}