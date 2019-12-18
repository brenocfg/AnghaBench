#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_18__ {size_t resp; } ;
typedef  TYPE_2__ client ;
struct TYPE_20__ {TYPE_1__* lua_client; } ;
struct TYPE_19__ {int /*<<< orphan*/ * null; int /*<<< orphan*/  cone; } ;
struct TYPE_17__ {int resp; } ;

/* Variables and functions */
#define  LUA_TBOOLEAN 131 
 int LUA_TNIL ; 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  addReply (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBool (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (TYPE_2__*) ; 
 int /*<<< orphan*/  addReplyDouble (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_2__*,long long) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_2__*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_strlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdscatprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsmapchars (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  sdsnew (scalar_t__) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_2__*,void*,int) ; 
 int /*<<< orphan*/  setDeferredMapLen (TYPE_2__*,void*,int) ; 
 int /*<<< orphan*/  setDeferredSetLen (TYPE_2__*,void*,int) ; 
 TYPE_3__ shared ; 

void luaReplyToRedisReply(client *c, lua_State *lua) {
    int t = lua_type(lua,-1);

    switch(t) {
    case LUA_TSTRING:
        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,-1),lua_strlen(lua,-1));
        break;
    case LUA_TBOOLEAN:
        if (server.lua_client->resp == 2)
            addReply(c,lua_toboolean(lua,-1) ? shared.cone :
                                               shared.null[c->resp]);
        else
            addReplyBool(c,lua_toboolean(lua,-1));
        break;
    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
        break;
    case LUA_TTABLE:
        /* We need to check if it is an array, an error, or a status reply.
         * Error are returned as a single element table with 'err' field.
         * Status replies are returned as single element table with 'ok'
         * field. */

        /* Handle error reply. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            sds err = sdsnew(lua_tostring(lua,-1));
            sdsmapchars(err,"\r\n","  ",2);
            addReplySds(c,sdscatprintf(sdsempty(),"-%s\r\n",err));
            sdsfree(err);
            lua_pop(lua,2);
            return;
        }
        lua_pop(lua,1); /* Discard field name pushed before. */

        /* Handle status reply. */
        lua_pushstring(lua,"ok");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            sds ok = sdsnew(lua_tostring(lua,-1));
            sdsmapchars(ok,"\r\n","  ",2);
            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
            sdsfree(ok);
            lua_pop(lua,2);
            return;
        }
        lua_pop(lua,1); /* Discard field name pushed before. */

        /* Handle double reply. */
        lua_pushstring(lua,"double");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TNUMBER) {
            addReplyDouble(c,lua_tonumber(lua,-1));
            lua_pop(lua,2);
            return;
        }
        lua_pop(lua,1); /* Discard field name pushed before. */

        /* Handle map reply. */
        lua_pushstring(lua,"map");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TTABLE) {
            int maplen = 0;
            void *replylen = addReplyDeferredLen(c);
            lua_pushnil(lua); /* Use nil to start iteration. */
            while (lua_next(lua,-2)) {
                /* Stack now: table, key, value */
                luaReplyToRedisReply(c, lua); /* Return value. */
                lua_pushvalue(lua,-1);        /* Dup key before consuming. */
                luaReplyToRedisReply(c, lua); /* Return key. */
                /* Stack now: table, key. */
                maplen++;
            }
            setDeferredMapLen(c,replylen,maplen);
            lua_pop(lua,2);
            return;
        }
        lua_pop(lua,1); /* Discard field name pushed before. */

        /* Handle set reply. */
        lua_pushstring(lua,"set");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TTABLE) {
            int setlen = 0;
            void *replylen = addReplyDeferredLen(c);
            lua_pushnil(lua); /* Use nil to start iteration. */
            while (lua_next(lua,-2)) {
                /* Stack now: table, key, true */
                lua_pop(lua,1);               /* Discard the boolean value. */
                lua_pushvalue(lua,-1);        /* Dup key before consuming. */
                luaReplyToRedisReply(c, lua); /* Return key. */
                /* Stack now: table, key. */
                setlen++;
            }
            setDeferredSetLen(c,replylen,setlen);
            lua_pop(lua,2);
            return;
        }
        lua_pop(lua,1); /* Discard field name pushed before. */

        /* Handle the array reply. */
        void *replylen = addReplyDeferredLen(c);
        int j = 1, mbulklen = 0;
        while(1) {
            lua_pushnumber(lua,j++);
            lua_gettable(lua,-2);
            t = lua_type(lua,-1);
            if (t == LUA_TNIL) {
                lua_pop(lua,1);
                break;
            }
            luaReplyToRedisReply(c, lua);
            mbulklen++;
        }
        setDeferredArrayLen(c,replylen,mbulklen);
        break;
    default:
        addReplyNull(c);
    }
    lua_pop(lua,1);
}