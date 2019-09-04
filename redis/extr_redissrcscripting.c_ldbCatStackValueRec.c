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
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LDB_MAX_VALUES_DEPTH ; 
#define  LUA_TBOOLEAN 136 
#define  LUA_TFUNCTION 135 
#define  LUA_TLIGHTUSERDATA 134 
#define  LUA_TNIL 133 
#define  LUA_TNUMBER 132 
#define  LUA_TSTRING 131 
#define  LUA_TTABLE 130 
#define  LUA_TTHREAD 129 
#define  LUA_TUSERDATA 128 
 int /*<<< orphan*/  lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 void* lua_topointer (int /*<<< orphan*/ *,int) ; 
 int const lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sdscatrepr (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  sdscatsds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

sds ldbCatStackValueRec(sds s, lua_State *lua, int idx, int level) {
    int t = lua_type(lua,idx);

    if (level++ == LDB_MAX_VALUES_DEPTH)
        return sdscat(s,"<max recursion level reached! Nested table?>");

    switch(t) {
    case LUA_TSTRING:
        {
        size_t strl;
        char *strp = (char*)lua_tolstring(lua,idx,&strl);
        s = sdscatrepr(s,strp,strl);
        }
        break;
    case LUA_TBOOLEAN:
        s = sdscat(s,lua_toboolean(lua,idx) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,idx));
        break;
    case LUA_TNIL:
        s = sdscatlen(s,"nil",3);
        break;
    case LUA_TTABLE:
        {
        int expected_index = 1; /* First index we expect in an array. */
        int is_array = 1; /* Will be set to null if check fails. */
        /* Note: we create two representations at the same time, one
         * assuming the table is an array, one assuming it is not. At the
         * end we know what is true and select the right one. */
        sds repr1 = sdsempty();
        sds repr2 = sdsempty();
        lua_pushnil(lua); /* The first key to start the iteration is nil. */
        while (lua_next(lua,idx-1)) {
            /* Test if so far the table looks like an array. */
            if (is_array &&
                (lua_type(lua,-2) != LUA_TNUMBER ||
                 lua_tonumber(lua,-2) != expected_index)) is_array = 0;
            /* Stack now: table, key, value */
            /* Array repr. */
            repr1 = ldbCatStackValueRec(repr1,lua,-1,level);
            repr1 = sdscatlen(repr1,"; ",2);
            /* Full repr. */
            repr2 = sdscatlen(repr2,"[",1);
            repr2 = ldbCatStackValueRec(repr2,lua,-2,level);
            repr2 = sdscatlen(repr2,"]=",2);
            repr2 = ldbCatStackValueRec(repr2,lua,-1,level);
            repr2 = sdscatlen(repr2,"; ",2);
            lua_pop(lua,1); /* Stack: table, key. Ready for next iteration. */
            expected_index++;
        }
        /* Strip the last " ;" from both the representations. */
        if (sdslen(repr1)) sdsrange(repr1,0,-3);
        if (sdslen(repr2)) sdsrange(repr2,0,-3);
        /* Select the right one and discard the other. */
        s = sdscatlen(s,"{",1);
        s = sdscatsds(s,is_array ? repr1 : repr2);
        s = sdscatlen(s,"}",1);
        sdsfree(repr1);
        sdsfree(repr2);
        }
        break;
    case LUA_TFUNCTION:
    case LUA_TUSERDATA:
    case LUA_TTHREAD:
    case LUA_TLIGHTUSERDATA:
        {
        const void *p = lua_topointer(lua,idx);
        char *typename = "unknown";
        if (t == LUA_TFUNCTION) typename = "function";
        else if (t == LUA_TUSERDATA) typename = "userdata";
        else if (t == LUA_TTHREAD) typename = "thread";
        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
        s = sdscatprintf(s,"\"%s@%p\"",typename,p);
        }
        break;
    default:
        s = sdscat(s,"\"<unknown-lua-type>\"");
        break;
    }
    return s;
}