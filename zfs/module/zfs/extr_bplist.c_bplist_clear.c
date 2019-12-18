#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bpl_lock; int /*<<< orphan*/  bpl_list; } ;
typedef  TYPE_1__ bplist_t ;
typedef  int /*<<< orphan*/  bplist_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * bplist_iterate_last_removed ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
bplist_clear(bplist_t *bpl)
{
	bplist_entry_t *bpe;

	mutex_enter(&bpl->bpl_lock);
	while ((bpe = list_head(&bpl->bpl_list))) {
		bplist_iterate_last_removed = bpe;
		list_remove(&bpl->bpl_list, bpe);
		kmem_free(bpe, sizeof (*bpe));
	}
	mutex_exit(&bpl->bpl_lock);
}