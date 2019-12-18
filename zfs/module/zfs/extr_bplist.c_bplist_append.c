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
struct TYPE_6__ {int /*<<< orphan*/  bpl_lock; int /*<<< orphan*/  bpl_list; } ;
typedef  TYPE_1__ bplist_t ;
struct TYPE_7__ {int /*<<< orphan*/  bpe_blk; } ;
typedef  TYPE_2__ bplist_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
bplist_append(bplist_t *bpl, const blkptr_t *bp)
{
	bplist_entry_t *bpe = kmem_alloc(sizeof (*bpe), KM_SLEEP);

	mutex_enter(&bpl->bpl_lock);
	bpe->bpe_blk = *bp;
	list_insert_tail(&bpl->bpl_list, bpe);
	mutex_exit(&bpl->bpl_lock);
}