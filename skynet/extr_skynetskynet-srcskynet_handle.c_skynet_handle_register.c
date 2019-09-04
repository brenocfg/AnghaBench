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
typedef  int uint32_t ;
struct skynet_context {int dummy; } ;
struct handle_storage {int handle_index; int slot_size; int harbor; struct skynet_context** slot; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct handle_storage* H ; 
 int HANDLE_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct skynet_context**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wunlock (int /*<<< orphan*/ *) ; 
 int skynet_context_handle (struct skynet_context*) ; 
 int /*<<< orphan*/  skynet_free (struct skynet_context**) ; 
 struct skynet_context** skynet_malloc (int) ; 

uint32_t
skynet_handle_register(struct skynet_context *ctx) {
	struct handle_storage *s = H;

	rwlock_wlock(&s->lock);
	
	for (;;) {
		int i;
		uint32_t handle = s->handle_index;
		for (i=0;i<s->slot_size;i++,handle++) {
			if (handle > HANDLE_MASK) {
				// 0 is reserved
				handle = 1;
			}
			int hash = handle & (s->slot_size-1);
			if (s->slot[hash] == NULL) {
				s->slot[hash] = ctx;
				s->handle_index = handle + 1;

				rwlock_wunlock(&s->lock);

				handle |= s->harbor;
				return handle;
			}
		}
		assert((s->slot_size*2 - 1) <= HANDLE_MASK);
		struct skynet_context ** new_slot = skynet_malloc(s->slot_size * 2 * sizeof(struct skynet_context *));
		memset(new_slot, 0, s->slot_size * 2 * sizeof(struct skynet_context *));
		for (i=0;i<s->slot_size;i++) {
			int hash = skynet_context_handle(s->slot[i]) & (s->slot_size * 2 - 1);
			assert(new_slot[hash] == NULL);
			new_slot[hash] = s->slot[i];
		}
		skynet_free(s->slot);
		s->slot = new_slot;
		s->slot_size *= 2;
	}
}