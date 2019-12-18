#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mh_nchains; struct TYPE_7__* mh_name; int /*<<< orphan*/  mh_contents; struct TYPE_7__* mh_next; } ;
typedef  TYPE_1__ mod_hash_t ;

/* Variables and functions */
 scalar_t__ MH_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* mh_head ; 
 int /*<<< orphan*/  mh_head_lock ; 
 int /*<<< orphan*/  mod_hash_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (TYPE_1__*) ; 

void
mod_hash_destroy_hash(mod_hash_t *hash)
{
	mod_hash_t *mhp, *mhpp;

	mutex_enter(&mh_head_lock);
	/*
	 * Remove the hash from the hash list
	 */
	if (hash == mh_head) {		/* removing 1st list elem */
		mh_head = mh_head->mh_next;
	} else {
		/*
		 * mhpp can start out NULL since we know the 1st elem isn't the
		 * droid we're looking for.
		 */
		mhpp = NULL;
		for (mhp = mh_head; mhp != NULL; mhp = mhp->mh_next) {
			if (mhp == hash) {
				mhpp->mh_next = mhp->mh_next;
				break;
			}
			mhpp = mhp;
		}
	}
	mutex_exit(&mh_head_lock);

	/*
	 * Clean out keys and values.
	 */
	mod_hash_clear(hash);

	rw_destroy(&hash->mh_contents);
	kmem_free(hash->mh_name, strlen(hash->mh_name) + 1);
	kmem_free(hash, MH_SIZE(hash->mh_nchains));
}