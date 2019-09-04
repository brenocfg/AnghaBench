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
struct TYPE_3__ {int type; scalar_t__ name; int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ table_field ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Integer ;
typedef  int /*<<< orphan*/  lua_CFunction ;

/* Variables and functions */
#define  LUA_TFUNCTION 131 
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static void set_fields(lua_State *L, int index, const table_field *fields) {
    for (int i = 0; fields[i].name; i++) {
        table_field f = fields[i];
        switch (f.value == NULL ? LUA_TNIL : f.type) {
            case LUA_TFUNCTION:
                lua_pushcfunction(L, (lua_CFunction) f.value);
                break;
            case LUA_TNUMBER:
                lua_pushinteger(L, *((lua_Integer *) f.value));
                break;
            case LUA_TSTRING:
                lua_pushstring(L, (const char *) f.value);
                break;
            case LUA_TNIL:
                lua_pushnil(L);
                break;
        }
        lua_setfield(L, index, f.name);
    }
}