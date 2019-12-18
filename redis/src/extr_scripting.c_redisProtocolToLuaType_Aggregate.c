#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {TYPE_1__* lua_client; } ;
struct TYPE_3__ {int resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 char* redisProtocolToLuaType (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__ server ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string2ll (char*,int,long long*) ; 

char *redisProtocolToLuaType_Aggregate(lua_State *lua, char *reply, int atype) {
    char *p = strchr(reply+1,'\r');
    long long mbulklen;
    int j = 0;

    string2ll(reply+1,p-reply-1,&mbulklen);
    if (server.lua_client->resp == 2 || atype == '*') {
        p += 2;
        if (mbulklen == -1) {
            lua_pushboolean(lua,0);
            return p;
        }
        lua_newtable(lua);
        for (j = 0; j < mbulklen; j++) {
            lua_pushnumber(lua,j+1);
            p = redisProtocolToLuaType(lua,p);
            lua_settable(lua,-3);
        }
    } else if (server.lua_client->resp == 3) {
        /* Here we handle only Set and Map replies in RESP3 mode, since arrays
         * follow the above RESP2 code path. Note that those are represented
         * as a table with the "map" or "set" field populated with the actual
         * table representing the set or the map type. */
        p += 2;
        lua_newtable(lua);
        lua_pushstring(lua,atype == '%' ? "map" : "set");
        lua_newtable(lua);
        for (j = 0; j < mbulklen; j++) {
            p = redisProtocolToLuaType(lua,p);
            if (atype == '%') {
                p = redisProtocolToLuaType(lua,p);
            } else {
                lua_pushboolean(lua,1);
            }
            lua_settable(lua,-3);
        }
        lua_settable(lua,-3);
    }
    return p;
}