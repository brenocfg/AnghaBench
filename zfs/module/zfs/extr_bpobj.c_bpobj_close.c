#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bpo_object; int /*<<< orphan*/  bpo_lock; int /*<<< orphan*/ * bpo_cached_dbuf; int /*<<< orphan*/ * bpo_phys; int /*<<< orphan*/ * bpo_dbuf; } ;
typedef  TYPE_1__ bpobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
bpobj_close(bpobj_t *bpo)
{
	/* Lame workaround for closing a bpobj that was never opened. */
	if (bpo->bpo_object == 0)
		return;

	dmu_buf_rele(bpo->bpo_dbuf, bpo);
	if (bpo->bpo_cached_dbuf != NULL)
		dmu_buf_rele(bpo->bpo_cached_dbuf, bpo);
	bpo->bpo_dbuf = NULL;
	bpo->bpo_phys = NULL;
	bpo->bpo_cached_dbuf = NULL;
	bpo->bpo_object = 0;

	mutex_destroy(&bpo->bpo_lock);
}