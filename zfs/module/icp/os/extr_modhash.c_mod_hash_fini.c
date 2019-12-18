#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mh_e_cache ; 
 int /*<<< orphan*/  mh_head_lock ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
mod_hash_fini(void)
{
	mutex_destroy(&mh_head_lock);

	if (mh_e_cache) {
		kmem_cache_destroy(mh_e_cache);
		mh_e_cache = NULL;
	}
}