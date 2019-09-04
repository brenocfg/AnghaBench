#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {size_t resp; } ;
typedef  TYPE_1__ client ;
struct TYPE_12__ {int /*<<< orphan*/ * null; int /*<<< orphan*/  cone; } ;

/* Variables and functions */
#define  LUA_TBOOLEAN 131 
 int LUA_TNIL ; 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  addReply (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addReplyBulkCBuffer (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 void* addReplyDeferredLen (TYPE_1__*) ; 
 int /*<<< orphan*/  addReplyLongLong (TYPE_1__*,long long) ; 
 int /*<<< orphan*/  addReplyNull (TYPE_1__*) ; 
 int /*<<< orphan*/  addReplySds (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
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
 int /*<<< orphan*/  setDeferredArrayLen (TYPE_1__*,void*,int) ; 
 TYPE_2__ shared ; 

void luaReplyToRedisReply(client *c, lua_State *lua) {
    int t = lua_type(lua,-1);

    switch(t) {
    case LUA_TSTRING:
        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,-1),lua_strlen(lua,-1));
        break;
    case LUA_TBOOLEAN:
        addReply(c,lua_toboolean(lua,-1) ? shared.cone : shared.null[c->resp]);
        break;
    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
        break;
    case LUA_TTABLE:
        /* We need to check if it is an array, an error, or a status reply.
         * Error are returned as a single element table with 'err' field.
         * Status replies are returned as single element table with 'ok'
         * field. */
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

        lua_pop(lua,1);
        lua_pushstring(lua,"ok");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            sds ok = sdsnew(lua_tostring(lua,-1));
            sdsmapchars(ok,"\r\n","  ",2);
            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
            sdsfree(ok);
            lua_pop(lua,1);
        } else {
            void *replylen = addReplyDeferredLen(c);
            int j = 1, mbulklen = 0;

            lua_pop(lua,1); /* Discard the 'ok' field value we popped */
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
        }
        break;
    default:
        addReplyNull(c);
    }
    lua_pop(lua,1);
}