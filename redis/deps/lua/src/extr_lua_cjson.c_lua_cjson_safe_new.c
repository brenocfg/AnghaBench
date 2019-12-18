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
 int /*<<< orphan*/  json_protect_conversion ; 
 int /*<<< orphan*/  lua_cjson_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 

__attribute__((used)) static int lua_cjson_safe_new(lua_State *l)
{
    const char *func[] = { "decode", "encode", NULL };
    int i;

    lua_cjson_new(l);

    /* Fix new() method */
    lua_pushcfunction(l, lua_cjson_safe_new);
    lua_setfield(l, -2, "new");

    for (i = 0; func[i]; i++) {
        lua_getfield(l, -1, func[i]);
        lua_pushcclosure(l, json_protect_conversion, 1);
        lua_setfield(l, -2, func[i]);
    }

    return 1;
}