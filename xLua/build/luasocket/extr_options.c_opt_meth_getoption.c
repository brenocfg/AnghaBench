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
typedef  int /*<<< orphan*/  p_socket ;
typedef  TYPE_1__* p_opt ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int (* func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int opt_meth_getoption(lua_State *L, p_opt opt, p_socket ps)
{
    const char *name = luaL_checkstring(L, 2);      /* obj, name, ... */
    while (opt->name && strcmp(name, opt->name))
        opt++;
    if (!opt->func) {
        char msg[45];
        sprintf(msg, "unsupported option `%.35s'", name);
        luaL_argerror(L, 2, msg);
    }
    return opt->func(L, ps);
}