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
struct buffer_node {int /*<<< orphan*/ * msg; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 struct buffer_node* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lfreepool(lua_State *L) {
	struct buffer_node * pool = lua_touserdata(L, 1);
	int sz = lua_rawlen(L,1) / sizeof(*pool);
	int i;
	for (i=0;i<sz;i++) {
		struct buffer_node *node = &pool[i];
		if (node->msg) {
			skynet_free(node->msg);
			node->msg = NULL;
		}
	}
	return 0;
}