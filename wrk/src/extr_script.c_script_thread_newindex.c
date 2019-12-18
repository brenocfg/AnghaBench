#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* addr; } ;
typedef  TYPE_1__ thread ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 struct addrinfo* checkaddr (int /*<<< orphan*/ *) ; 
 TYPE_1__* checkthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_addr_copy (struct addrinfo*,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ) ; 
 TYPE_2__* zrealloc (TYPE_2__*,int) ; 

__attribute__((used)) static int script_thread_newindex(lua_State *L) {
    thread *t = checkthread(L);
    const char *key = lua_tostring(L, -2);
    if (!strcmp("addr", key)) {
        struct addrinfo *addr = checkaddr(L);
        if (t->addr) zfree(t->addr->ai_addr);
        t->addr = zrealloc(t->addr, sizeof(*addr));
        script_addr_copy(addr, t->addr);
    } else {
        luaL_error(L, "cannot set '%s' on thread", luaL_typename(L, -1));
    }
    return 0;
}