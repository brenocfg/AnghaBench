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
struct linger {int /*<<< orphan*/  l_linger; int /*<<< orphan*/  l_onoff; } ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  li ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int opt_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

int opt_get_linger(lua_State *L, p_socket ps)
{
    struct linger li;                      /* obj, name */
    int len = sizeof(li);
    int err = opt_get(L, ps, SOL_SOCKET, SO_LINGER, (char *) &li, &len);
    if (err)
        return err;
    lua_newtable(L);
    lua_pushboolean(L, li.l_onoff);
    lua_setfield(L, -2, "on");
    lua_pushinteger(L, li.l_linger);
    lua_setfield(L, -2, "timeout");
    return 1;
}