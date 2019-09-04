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
typedef  int /*<<< orphan*/  strbuf_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  json_config_t ;

/* Variables and functions */
 int LUA_TNUMBER ; 
 int LUA_TSTRING ; 
 int /*<<< orphan*/  json_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_append_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_encode_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_append_char (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_append_mem (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void json_append_object(lua_State *l, json_config_t *cfg,
                               int current_depth, strbuf_t *json)
{
    int comma, keytype;

    /* Object */
    strbuf_append_char(json, '{');

    lua_pushnil(l);
    /* table, startkey */
    comma = 0;
    while (lua_next(l, -2) != 0) {
        if (comma)
            strbuf_append_char(json, ',');
        else
            comma = 1;

        /* table, key, value */
        keytype = lua_type(l, -2);
        if (keytype == LUA_TNUMBER) {
            strbuf_append_char(json, '"');
            json_append_number(l, cfg, json, -2);
            strbuf_append_mem(json, "\":", 2);
        } else if (keytype == LUA_TSTRING) {
            json_append_string(l, json, -2);
            strbuf_append_char(json, ':');
        } else {
            json_encode_exception(l, cfg, json, -2,
                                  "table key must be a number or string");
            /* never returns */
        }

        /* table, key, value */
        json_append_data(l, cfg, current_depth, json);
        lua_pop(l, 1);
        /* table, key */
    }

    strbuf_append_char(json, '}');
}