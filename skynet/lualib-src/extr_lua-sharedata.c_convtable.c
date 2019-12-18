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
typedef  union value {int dummy; } value ;
typedef  void* uint8_t ;
struct table {int sizearray; int sizehash; struct node* hash; union value* array; void** arraytype; int /*<<< orphan*/  L; } ;
struct node {scalar_t__ nocolliding; void* valuetype; } ;
struct context {int /*<<< orphan*/  L; struct table* tbl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* VALUETYPE_NIL ; 
 int countsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fillcolliding (int /*<<< orphan*/ *,struct context*) ; 
 int /*<<< orphan*/  fillnocolliding (int /*<<< orphan*/ *,struct context*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int lua_rawlen (int /*<<< orphan*/ *,int) ; 
 struct context* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setarray (struct context*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
convtable(lua_State *L) {
	int i;
	struct context *ctx = lua_touserdata(L,2);
	struct table *tbl = ctx->tbl;

	tbl->L = ctx->L;

	int sizearray = lua_rawlen(L, 1);
	if (sizearray) {
		tbl->arraytype = (uint8_t *)malloc(sizearray * sizeof(uint8_t));
		if (tbl->arraytype == NULL) {
			goto memerror;
		}
		for (i=0;i<sizearray;i++) {
			tbl->arraytype[i] = VALUETYPE_NIL;
		}
		tbl->array = (union value *)malloc(sizearray * sizeof(union value));
		if (tbl->array == NULL) {
			goto memerror;
		}
		tbl->sizearray = sizearray;
	}
	int sizehash = countsize(L, sizearray);
	if (sizehash) {
		tbl->hash = (struct node *)malloc(sizehash * sizeof(struct node));
		if (tbl->hash == NULL) {
			goto memerror;
		}
		for (i=0;i<sizehash;i++) {
			tbl->hash[i].valuetype = VALUETYPE_NIL;
			tbl->hash[i].nocolliding = 0;
		}
		tbl->sizehash = sizehash;

		fillnocolliding(L, ctx);
		fillcolliding(L, ctx);
	} else {
		int i;
		for (i=1;i<=sizearray;i++) {
			lua_rawgeti(L, 1, i);
			setarray(ctx, L, -1, i);
			lua_pop(L,1);
		}
	}

	return 0;
memerror:
	return luaL_error(L, "memory error");
}