#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  free; scalar_t__ b; } ;
typedef  TYPE_1__ mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_argerror (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_buf_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* mp_buf_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_encode_lua_type (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

int mp_pack(lua_State *L) {
    int nargs = lua_gettop(L);
    int i;
    mp_buf *buf;

    if (nargs == 0)
        return luaL_argerror(L, 0, "MessagePack pack needs input.");

    if (!lua_checkstack(L, nargs))
        return luaL_argerror(L, 0, "Too many arguments for MessagePack pack.");

    buf = mp_buf_new(L);
    for(i = 1; i <= nargs; i++) {
        /* Copy argument i to top of stack for _encode processing;
         * the encode function pops it from the stack when complete. */
        luaL_checkstack(L, 1, "in function mp_check");
        lua_pushvalue(L, i);

        mp_encode_lua_type(L,buf,0);

        lua_pushlstring(L,(char*)buf->b,buf->len);

        /* Reuse the buffer for the next operation by
         * setting its free count to the total buffer size
         * and the current position to zero. */
        buf->free += buf->len;
        buf->len = 0;
    }
    mp_buf_free(L, buf);

    /* Concatenate all nargs buffers together */
    lua_concat(L, nargs);
    return 1;
}