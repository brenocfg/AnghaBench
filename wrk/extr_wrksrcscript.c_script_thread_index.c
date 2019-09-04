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
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ thread ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* checkthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_addr_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_thread_get ; 
 int /*<<< orphan*/  script_thread_set ; 
 int /*<<< orphan*/  script_thread_stop ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int script_thread_index(lua_State *L) {
    thread *t = checkthread(L);
    const char *key = lua_tostring(L, 2);
    if (!strcmp("get",  key)) lua_pushcfunction(L, script_thread_get);
    if (!strcmp("set",  key)) lua_pushcfunction(L, script_thread_set);
    if (!strcmp("stop", key)) lua_pushcfunction(L, script_thread_stop);
    if (!strcmp("addr", key)) script_addr_clone(L, t->addr);
    return 1;
}