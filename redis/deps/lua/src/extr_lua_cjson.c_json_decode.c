#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ json_token_t ;
struct TYPE_10__ {int /*<<< orphan*/  tmp; int /*<<< orphan*/ * data; int /*<<< orphan*/ * ptr; scalar_t__ current_depth; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_2__ json_parse_t ;

/* Variables and functions */
 scalar_t__ T_END ; 
 int /*<<< orphan*/  json_fetch_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_next_token (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  json_process_value (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  json_throw_parse_error (int /*<<< orphan*/ *,TYPE_2__*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/ * luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_new (size_t) ; 

__attribute__((used)) static int json_decode(lua_State *l)
{
    json_parse_t json;
    json_token_t token;
    size_t json_len;

    luaL_argcheck(l, lua_gettop(l) == 1, 1, "expected 1 argument");

    json.cfg = json_fetch_config(l);
    json.data = luaL_checklstring(l, 1, &json_len);
    json.current_depth = 0;
    json.ptr = json.data;

    /* Detect Unicode other than UTF-8 (see RFC 4627, Sec 3)
     *
     * CJSON can support any simple data type, hence only the first
     * character is guaranteed to be ASCII (at worst: '"'). This is
     * still enough to detect whether the wrong encoding is in use. */
    if (json_len >= 2 && (!json.data[0] || !json.data[1]))
        luaL_error(l, "JSON parser does not support UTF-16 or UTF-32");

    /* Ensure the temporary buffer can hold the entire string.
     * This means we no longer need to do length checks since the decoded
     * string must be smaller than the entire json string */
    json.tmp = strbuf_new(json_len);

    json_next_token(&json, &token);
    json_process_value(l, &json, &token);

    /* Ensure there is no more input left */
    json_next_token(&json, &token);

    if (token.type != T_END)
        json_throw_parse_error(l, &json, "the end", &token);

    strbuf_free(json.tmp);

    return 1;
}