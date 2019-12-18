#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t left; scalar_t__ err; } ;
typedef  TYPE_1__ mp_cur ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ MP_CUR_ERROR_BADFMT ; 
 scalar_t__ MP_CUR_ERROR_EOF ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_cur_init (TYPE_1__*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mp_decode_to_lua_type (int /*<<< orphan*/ *,TYPE_1__*) ; 

int mp_unpack_full(lua_State *L, int limit, int offset) {
    size_t len;
    const char *s;
    mp_cur c;
    int cnt; /* Number of objects unpacked */
    int decode_all = (!limit && !offset);

    s = luaL_checklstring(L,1,&len); /* if no match, exits */

    if (offset < 0 || limit < 0) /* requesting negative off or lim is invalid */
        return luaL_error(L,
            "Invalid request to unpack with offset of %d and limit of %d.",
            offset, len);
    else if (offset > len)
        return luaL_error(L,
            "Start offset %d greater than input length %d.", offset, len);

    if (decode_all) limit = INT_MAX;

    mp_cur_init(&c,(const unsigned char *)s+offset,len-offset);

    /* We loop over the decode because this could be a stream
     * of multiple top-level values serialized together */
    for(cnt = 0; c.left > 0 && cnt < limit; cnt++) {
        mp_decode_to_lua_type(L,&c);

        if (c.err == MP_CUR_ERROR_EOF) {
            return luaL_error(L,"Missing bytes in input.");
        } else if (c.err == MP_CUR_ERROR_BADFMT) {
            return luaL_error(L,"Bad data format in input.");
        }
    }

    if (!decode_all) {
        /* c->left is the remaining size of the input buffer.
         * subtract the entire buffer size from the unprocessed size
         * to get our next start offset */
        int offset = len - c.left;

        luaL_checkstack(L, 1, "in function mp_unpack_full");

        /* Return offset -1 when we have have processed the entire buffer. */
        lua_pushinteger(L, c.left == 0 ? -1 : offset);
        /* Results are returned with the arg elements still
         * in place. Lua takes care of only returning
         * elements above the args for us.
         * In this case, we have one arg on the stack
         * for this function, so we insert our first return
         * value at position 2. */
        lua_insert(L, 2);
        cnt += 1; /* increase return count by one to make room for offset */
    }

    return cnt;
}