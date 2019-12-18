#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p_timeout ;
typedef  TYPE_2__* p_buffer ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_8__ {TYPE_1__* io; int /*<<< orphan*/  tm; } ;
struct TYPE_7__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* error ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int IO_DONE ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_optlstring (int /*<<< orphan*/ *,int,char*,size_t*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 double lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int recvall (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int recvline (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int recvraw (TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timeout_getstart (int /*<<< orphan*/ ) ; 
 scalar_t__ timeout_gettime () ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ ) ; 

int buffer_meth_receive(lua_State *L, p_buffer buf) {
    int err = IO_DONE, top = lua_gettop(L);
    luaL_Buffer b;
    size_t size;
    const char *part = luaL_optlstring(L, 3, "", &size);
#ifdef LUASOCKET_DEBUG
    p_timeout tm = timeout_markstart(buf->tm);
#endif
    /* initialize buffer with optional extra prefix 
     * (useful for concatenating previous partial results) */
    luaL_buffinit(L, &b);
    luaL_addlstring(&b, part, size);
    /* receive new patterns */
    if (!lua_isnumber(L, 2)) {
        const char *p= luaL_optstring(L, 2, "*l");
        if (p[0] == '*' && p[1] == 'l') err = recvline(buf, &b);
        else if (p[0] == '*' && p[1] == 'a') err = recvall(buf, &b); 
        else luaL_argcheck(L, 0, 2, "invalid receive pattern");
    /* get a fixed number of bytes (minus what was already partially 
     * received) */
    } else {
        double n = lua_tonumber(L, 2); 
        size_t wanted = (size_t) n;
        luaL_argcheck(L, n >= 0, 2, "invalid receive pattern");
        if (size == 0 || wanted > size)
            err = recvraw(buf, wanted-size, &b);
    }
    /* check if there was an error */
    if (err != IO_DONE) {
        /* we can't push anyting in the stack before pushing the
         * contents of the buffer. this is the reason for the complication */
        luaL_pushresult(&b);
        lua_pushstring(L, buf->io->error(buf->io->ctx, err)); 
        lua_pushvalue(L, -2); 
        lua_pushnil(L);
        lua_replace(L, -4);
    } else {
        luaL_pushresult(&b);
        lua_pushnil(L);
        lua_pushnil(L);
    }
#ifdef LUASOCKET_DEBUG
    /* push time elapsed during operation as the last return value */
    lua_pushnumber(L, timeout_gettime() - timeout_getstart(tm));
#endif
    return lua_gettop(L) - top;
}