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
struct queue {int head; int tail; int cap; struct netpack* queue; int /*<<< orphan*/ ** hash; } ;
struct netpack {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int HASHSIZE ; 
 int /*<<< orphan*/  clear_list (int /*<<< orphan*/ *) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lclear(lua_State *L) {
	struct queue * q = lua_touserdata(L, 1);
	if (q == NULL) {
		return 0;
	}
	int i;
	for (i=0;i<HASHSIZE;i++) {
		clear_list(q->hash[i]);
		q->hash[i] = NULL;
	}
	if (q->head > q->tail) {
		q->tail += q->cap;
	}
	for (i=q->head;i<q->tail;i++) {
		struct netpack *np = &q->queue[i % q->cap];
		skynet_free(np->buffer);
	}
	q->head = q->tail = 0;

	return 0;
}