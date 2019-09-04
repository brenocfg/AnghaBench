#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ thread ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* checkthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_copy_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int script_thread_get(lua_State *L) {
    thread *t = checkthread(L);
    const char *key = lua_tostring(L, -1);
    lua_getglobal(t->L, key);
    script_copy_value(t->L, L, -1);
    lua_pop(t->L, 1);
    return 1;
}