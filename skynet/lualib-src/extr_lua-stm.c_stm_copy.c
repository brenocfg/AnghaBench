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
struct stm_object {int /*<<< orphan*/  lock; struct stm_copy* copy; } ;
struct stm_copy {int /*<<< orphan*/  reference; } ;

/* Variables and functions */
 int ATOM_FINC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rwlock_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_runlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct stm_copy *
stm_copy(struct stm_object *obj) {
	rwlock_rlock(&obj->lock);
	struct stm_copy * ret = obj->copy;
	if (ret) {
		int ref = ATOM_FINC(&ret->reference);
		assert(ref > 0);
	}
	rwlock_runlock(&obj->lock);
	
	return ret;
}