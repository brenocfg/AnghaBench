#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p_timeout ;
typedef  TYPE_2__* p_buffer ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ lua_Number ;
struct TYPE_6__ {TYPE_1__* io; int /*<<< orphan*/  tm; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* error ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int IO_DONE ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sendraw (TYPE_2__*,char const*,long,size_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timeout_getstart (int /*<<< orphan*/ ) ; 
 scalar_t__ timeout_gettime () ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ ) ; 

int buffer_meth_send(lua_State *L, p_buffer buf) {
    int top = lua_gettop(L);
    int err = IO_DONE;
    size_t size = 0, sent = 0;
    const char *data = luaL_checklstring(L, 2, &size);
    long start = (long) luaL_optnumber(L, 3, 1);
    long end = (long) luaL_optnumber(L, 4, -1);
#ifdef LUASOCKET_DEBUG
    p_timeout tm = timeout_markstart(buf->tm);
#endif
    if (start < 0) start = (long) (size+start+1);
    if (end < 0) end = (long) (size+end+1);
    if (start < 1) start = (long) 1;
    if (end > (long) size) end = (long) size;
    if (start <= end) err = sendraw(buf, data+start-1, end-start+1, &sent);
    /* check if there was an error */
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, buf->io->error(buf->io->ctx, err)); 
        lua_pushnumber(L, (lua_Number) (sent+start-1));
    } else {
        lua_pushnumber(L, (lua_Number) (sent+start-1));
        lua_pushnil(L);
        lua_pushnil(L);
    }
#ifdef LUASOCKET_DEBUG
    /* push time elapsed during operation as the last return value */
    lua_pushnumber(L, timeout_gettime() - timeout_getstart(tm));
#endif
    return lua_gettop(L) - top;
}