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
 int MAX_LONG_DOUBLE_CHARS ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strchr (char*,char) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 

char *redisProtocolToLuaType_Double(lua_State *lua, char *reply) {
    char *p = strchr(reply+1,'\r');
    char buf[MAX_LONG_DOUBLE_CHARS+1];
    size_t len = p-reply-1;
    double d;

    if (len <= MAX_LONG_DOUBLE_CHARS) {
        memcpy(buf,reply+1,len);
        buf[len] = '\0';
        d = strtod(buf,NULL); /* We expect a valid representation. */
    } else {
        d = 0;
    }

    lua_newtable(lua);
    lua_pushstring(lua,"double");
    lua_pushnumber(lua,d);
    lua_settable(lua,-3);
    return p+2;
}