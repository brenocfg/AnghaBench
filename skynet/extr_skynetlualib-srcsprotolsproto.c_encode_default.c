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
struct sproto_arg {scalar_t__ index; int /*<<< orphan*/  tagname; int /*<<< orphan*/ * ud; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SPROTO_CB_NIL ; 
 int SPROTO_CB_NOARRAY ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  push_default (struct sproto_arg const*,int) ; 

__attribute__((used)) static int
encode_default(const struct sproto_arg *args) {
	lua_State *L = args->ud;
	lua_pushstring(L, args->tagname);
	if (args->index > 0) {
		lua_newtable(L);
		push_default(args, 1);
		lua_setfield(L, -2, "__array");
		lua_rawset(L, -3);
		return SPROTO_CB_NOARRAY;
	} else {
		push_default(args, 0);
		lua_rawset(L, -3);
		return SPROTO_CB_NIL;
	}
}