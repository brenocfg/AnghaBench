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
 char* redisProtocolToLuaType_Aggregate (int /*<<< orphan*/ *,char*,char) ; 
 char* redisProtocolToLuaType_Bool (int /*<<< orphan*/ *,char*,char) ; 
 char* redisProtocolToLuaType_Bulk (int /*<<< orphan*/ *,char*) ; 
 char* redisProtocolToLuaType_Double (int /*<<< orphan*/ *,char*) ; 
 char* redisProtocolToLuaType_Error (int /*<<< orphan*/ *,char*) ; 
 char* redisProtocolToLuaType_Int (int /*<<< orphan*/ *,char*) ; 
 char* redisProtocolToLuaType_Null (int /*<<< orphan*/ *,char*) ; 
 char* redisProtocolToLuaType_Status (int /*<<< orphan*/ *,char*) ; 

char *redisProtocolToLuaType(lua_State *lua, char* reply) {
    char *p = reply;

    switch(*p) {
    case ':': p = redisProtocolToLuaType_Int(lua,reply); break;
    case '$': p = redisProtocolToLuaType_Bulk(lua,reply); break;
    case '+': p = redisProtocolToLuaType_Status(lua,reply); break;
    case '-': p = redisProtocolToLuaType_Error(lua,reply); break;
    case '*': p = redisProtocolToLuaType_Aggregate(lua,reply,*p); break;
    case '%': p = redisProtocolToLuaType_Aggregate(lua,reply,*p); break;
    case '~': p = redisProtocolToLuaType_Aggregate(lua,reply,*p); break;
    case '_': p = redisProtocolToLuaType_Null(lua,reply); break;
    case '#': p = redisProtocolToLuaType_Bool(lua,reply,p[1]); break;
    case ',': p = redisProtocolToLuaType_Double(lua,reply); break;
    }
    return p;
}