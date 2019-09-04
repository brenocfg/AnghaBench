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
typedef  size_t uint32_t ;
struct table {size_t sizehash; struct node* hash; } ;
struct node {scalar_t__ valuetype; int key; int keytype; size_t keyhash; int next; int nocolliding; } ;
struct context {struct table* tbl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ VALUETYPE_NIL ; 
 int /*<<< orphan*/  ishashkey (struct context*,int /*<<< orphan*/ *,int,int*,size_t*,int*) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setarray (struct context*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  setvalue (struct context*,int /*<<< orphan*/ *,int,struct node*) ; 

__attribute__((used)) static void
fillnocolliding(lua_State *L, struct context *ctx) {
	struct table * tbl = ctx->tbl;
	lua_pushnil(L);
	while (lua_next(L, 1) != 0) {
		int key;
		int keytype;
		uint32_t keyhash;
		if (!ishashkey(ctx, L, -2, &key, &keyhash, &keytype)) {
			setarray(ctx, L, -1, key);
		} else {
			struct node * n = &tbl->hash[keyhash % tbl->sizehash];
			if (n->valuetype == VALUETYPE_NIL) {
				n->key = key;
				n->keytype = keytype;
				n->keyhash = keyhash;
				n->next = -1;
				n->nocolliding = 1;
				setvalue(ctx, L, -1, n);	// set n->v , n->valuetype
			}
		}
		lua_pop(L,1);
	}
}