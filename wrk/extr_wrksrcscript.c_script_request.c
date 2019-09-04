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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* realloc (char*,size_t) ; 

void script_request(lua_State *L, char **buf, size_t *len) {
    int pop = 1;
    lua_getglobal(L, "request");
    if (!lua_isfunction(L, -1)) {
        lua_getglobal(L, "wrk");
        lua_getfield(L, -1, "request");
        pop += 2;
    }
    lua_call(L, 0, 1);
    const char *str = lua_tolstring(L, -1, len);
    *buf = realloc(*buf, *len);
    memcpy(*buf, str, *len);
    lua_pop(L, pop);
}