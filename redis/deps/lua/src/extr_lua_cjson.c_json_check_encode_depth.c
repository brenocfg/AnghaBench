#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int encode_max_depth; int /*<<< orphan*/  encode_keep_buffer; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void json_check_encode_depth(lua_State *l, json_config_t *cfg,
                                    int current_depth, strbuf_t *json)
{
    /* Ensure there are enough slots free to traverse a table (key,
     * value) and push a string for a potential error message.
     *
     * Unlike "decode", the key and value are still on the stack when
     * lua_checkstack() is called.  Hence an extra slot for luaL_error()
     * below is required just in case the next check to lua_checkstack()
     * fails.
     *
     * While this won't cause a crash due to the EXTRA_STACK reserve
     * slots, it would still be an improper use of the API. */
    if (current_depth <= cfg->encode_max_depth && lua_checkstack(l, 3))
        return;

    if (!cfg->encode_keep_buffer)
        strbuf_free(json);

    luaL_error(l, "Cannot serialise, excessive nesting (%d)",
               current_depth);
}