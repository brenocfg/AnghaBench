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
struct queue {int /*<<< orphan*/ ** hash; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  cap; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int HASHSIZE ; 
 int /*<<< orphan*/  QUEUESIZE ; 
 struct queue* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct queue *
get_queue(lua_State *L) {
	struct queue *q = lua_touserdata(L,1);
	if (q == NULL) {
		q = lua_newuserdata(L, sizeof(struct queue));
		q->cap = QUEUESIZE;
		q->head = 0;
		q->tail = 0;
		int i;
		for (i=0;i<HASHSIZE;i++) {
			q->hash[i] = NULL;
		}
		lua_replace(L, 1);
	}
	return q;
}