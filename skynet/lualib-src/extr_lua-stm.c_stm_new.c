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
struct stm_object {int reference; int /*<<< orphan*/  copy; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 struct stm_object* skynet_malloc (int) ; 
 int /*<<< orphan*/  stm_newcopy (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stm_object *
stm_new(void * msg, int32_t sz) {
	struct stm_object * obj = skynet_malloc(sizeof(*obj));
	rwlock_init(&obj->lock);
	obj->reference = 1;
	obj->copy = stm_newcopy(msg, sz);

	return obj;
}