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
typedef  int /*<<< orphan*/  uint32_t ;
struct table {int array; int dict; int /*<<< orphan*/ * type; } ;
struct proxy {scalar_t__ index; scalar_t__ data; } ;
struct document {scalar_t__ n; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_STRING ; 
 struct table* gettable (struct document const*,scalar_t__) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct document const*) ; 

__attribute__((used)) static void
copytable(lua_State *L, int tbl, struct proxy *p) {
	const struct document * doc = (const struct document *)p->data; 
	if (p->index < 0 || p->index >= doc->n) {
		luaL_error(L, "Invalid proxy (index = %d, total = %d)", p->index, (int)doc->n);
	}
	const struct table * t = gettable(doc, p->index);
	if (t == NULL) {
		luaL_error(L, "Invalid proxy (index = %d)", p->index);
	}
	const uint32_t * v = (const uint32_t *)((const char *)t + sizeof(uint32_t) + sizeof(uint32_t) + ((t->array + t->dict + 3) & ~3));
	int i;
	for (i=0;i<t->array;i++) {
		pushvalue(L, v++, t->type[i], doc);
		lua_rawseti(L, tbl, i+1);
	}
	for (i=0;i<t->dict;i++) {
		pushvalue(L, v++, VALUE_STRING, doc);
		pushvalue(L, v++, t->type[t->array+i], doc);
		lua_rawset(L, tbl);
	}
}