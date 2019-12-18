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
struct queue {size_t tail; size_t cap; size_t head; struct netpack* queue; } ;
struct netpack {int id; int size; void* buffer; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  expand_queue (int /*<<< orphan*/ *,struct queue*) ; 
 struct queue* get_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 void* skynet_malloc (int) ; 

__attribute__((used)) static void
push_data(lua_State *L, int fd, void *buffer, int size, int clone) {
	if (clone) {
		void * tmp = skynet_malloc(size);
		memcpy(tmp, buffer, size);
		buffer = tmp;
	}
	struct queue *q = get_queue(L);
	struct netpack *np = &q->queue[q->tail];
	if (++q->tail >= q->cap)
		q->tail -= q->cap;
	np->id = fd;
	np->buffer = buffer;
	np->size = size;
	if (q->head == q->tail) {
		expand_queue(L, q);
	}
}