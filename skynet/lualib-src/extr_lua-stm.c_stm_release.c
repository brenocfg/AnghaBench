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
struct stm_object {scalar_t__ reference; int /*<<< orphan*/  lock; int /*<<< orphan*/ * copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_free (struct stm_object*) ; 
 int /*<<< orphan*/  stm_releasecopy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stm_release(struct stm_object *obj) {
	assert(obj->copy);
	rwlock_wlock(&obj->lock);
	// writer release the stm object, so release the last copy .
	stm_releasecopy(obj->copy);
	obj->copy = NULL;
	if (--obj->reference > 0) {
		// stm object grab by readers, reset the copy to NULL.
		rwlock_wunlock(&obj->lock);
		return;
	}
	// no one grab the stm object, no need to unlock wlock.
	skynet_free(obj);
}