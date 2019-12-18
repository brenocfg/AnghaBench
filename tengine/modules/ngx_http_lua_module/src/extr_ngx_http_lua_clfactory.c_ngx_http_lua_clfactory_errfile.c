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
 int LUA_ERRFILE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static int
ngx_http_lua_clfactory_errfile(lua_State *L, const char *what, int fname_index)
{
    const char      *serr;
    const char      *filename;

    filename = lua_tostring(L, fname_index) + 1;

    if (errno) {
        serr = strerror(errno);
        lua_pushfstring(L, "cannot %s %s: %s", what, filename, serr);

    } else {
        lua_pushfstring(L, "cannot %s %s", what, filename);
    }

    lua_remove(L, fname_index);

    return LUA_ERRFILE;
}