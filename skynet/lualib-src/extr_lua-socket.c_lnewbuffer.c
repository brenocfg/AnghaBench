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
struct socket_buffer {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; scalar_t__ offset; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct socket_buffer* lua_newuserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lnewbuffer(lua_State *L) {
	struct socket_buffer * sb = lua_newuserdata(L, sizeof(*sb));	
	sb->size = 0;
	sb->offset = 0;
	sb->head = NULL;
	sb->tail = NULL;
	
	return 1;
}