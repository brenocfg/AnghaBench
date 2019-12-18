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
struct queue {size_t head; size_t tail; size_t cap; struct netpack* queue; } ;
struct netpack {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct queue* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lpop(lua_State *L) {
	struct queue * q = lua_touserdata(L, 1);
	if (q == NULL || q->head == q->tail)
		return 0;
	struct netpack *np = &q->queue[q->head];
	if (++q->head >= q->cap) {
		q->head = 0;
	}
	lua_pushinteger(L, np->id);
	lua_pushlightuserdata(L, np->buffer);
	lua_pushinteger(L, np->size);

	return 3;
}