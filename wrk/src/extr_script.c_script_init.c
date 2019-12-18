#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ thread ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  script_push_thread (int /*<<< orphan*/ *,TYPE_1__*) ; 

void script_init(lua_State *L, thread *t, int argc, char **argv) {
    lua_getglobal(t->L, "wrk");

    script_push_thread(t->L, t);
    lua_setfield(t->L, -2, "thread");

    lua_getglobal(L, "wrk");
    lua_getfield(L, -1, "setup");
    script_push_thread(L, t);
    lua_call(L, 1, 0);
    lua_pop(L, 1);

    lua_getfield(t->L, -1, "init");
    lua_newtable(t->L);
    for (int i = 0; i < argc; i++) {
        lua_pushstring(t->L, argv[i]);
        lua_rawseti(t->L, -2, i);
    }
    lua_call(t->L, 1, 0);
    lua_pop(t->L, 1);
}