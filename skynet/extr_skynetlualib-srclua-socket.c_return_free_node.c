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
struct socket_buffer {int /*<<< orphan*/ * tail; struct buffer_node* head; scalar_t__ offset; } ;
struct buffer_node {scalar_t__ sz; int /*<<< orphan*/ * msg; struct buffer_node* next; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct buffer_node*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 struct buffer_node* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
return_free_node(lua_State *L, int pool, struct socket_buffer *sb) {
	struct buffer_node *free_node = sb->head;
	sb->offset = 0;
	sb->head = free_node->next;
	if (sb->head == NULL) {
		sb->tail = NULL;
	}
	lua_rawgeti(L,pool,1);
	free_node->next = lua_touserdata(L,-1);
	lua_pop(L,1);
	skynet_free(free_node->msg);
	free_node->msg = NULL;

	free_node->sz = 0;
	lua_pushlightuserdata(L, free_node);
	lua_rawseti(L, pool, 1);
}