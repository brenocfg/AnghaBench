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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/ * p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int,int,char*,int*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static 
int opt_get(lua_State *L, p_socket ps, int level, int name, void *val, int* len)
{
    socklen_t socklen = *len;
    if (getsockopt(*ps, level, name, (char *) val, &socklen) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "getsockopt failed");
        return 2;
    }
    *len = socklen;
    return 0;
}