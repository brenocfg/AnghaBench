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
 int luaL_checkoption (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int json_enum_option(lua_State *l, int optindex, int *setting,
                            const char **options, int bool_true)
{
    static const char *bool_options[] = { "off", "on", NULL };

    if (!options) {
        options = bool_options;
        bool_true = 1;
    }

    if (!lua_isnil(l, optindex)) {
        if (bool_true && lua_isboolean(l, optindex))
            *setting = lua_toboolean(l, optindex) * bool_true;
        else
            *setting = luaL_checkoption(l, optindex, NULL, options);
    }

    if (bool_true && (*setting == 0 || *setting == bool_true))
        lua_pushboolean(l, *setting);
    else
        lua_pushstring(l, options[*setting]);

    return 1;
}