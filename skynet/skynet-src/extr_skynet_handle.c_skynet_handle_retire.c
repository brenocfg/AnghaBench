#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct skynet_context {int dummy; } ;
struct handle_storage {int slot_size; int name_count; int /*<<< orphan*/  lock; TYPE_1__* name; struct skynet_context** slot; } ;
struct TYPE_2__ {int handle; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct handle_storage* H ; 
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 
 int skynet_context_handle (struct skynet_context*) ; 
 int /*<<< orphan*/  skynet_context_release (struct skynet_context*) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 

int
skynet_handle_retire(uint32_t handle) {
	int ret = 0;
	struct handle_storage *s = H;

	rwlock_wlock(&s->lock);

	uint32_t hash = handle & (s->slot_size-1);
	struct skynet_context * ctx = s->slot[hash];

	if (ctx != NULL && skynet_context_handle(ctx) == handle) {
		s->slot[hash] = NULL;
		ret = 1;
		int i;
		int j=0, n=s->name_count;
		for (i=0; i<n; ++i) {
			if (s->name[i].handle == handle) {
				skynet_free(s->name[i].name);
				continue;
			} else if (i!=j) {
				s->name[j] = s->name[i];
			}
			++j;
		}
		s->name_count = j;
	} else {
		ctx = NULL;
	}

	rwlock_wunlock(&s->lock);

	if (ctx) {
		// release ctx may call skynet_handle_* , so wunlock first.
		skynet_context_release(ctx);
	}

	return ret;
}