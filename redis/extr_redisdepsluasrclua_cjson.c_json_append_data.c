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
#define  LUA_TBOOLEAN 133 
#define  LUA_TLIGHTUSERDATA 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  json_append_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_append_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_append_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_check_encode_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_encode_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int lua_array_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_append_mem (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void json_append_data(lua_State *l, json_config_t *cfg,
                             int current_depth, strbuf_t *json)
{
    int len;

    switch (lua_type(l, -1)) {
    case LUA_TSTRING:
        json_append_string(l, json, -1);
        break;
    case LUA_TNUMBER:
        json_append_number(l, cfg, json, -1);
        break;
    case LUA_TBOOLEAN:
        if (lua_toboolean(l, -1))
            strbuf_append_mem(json, "true", 4);
        else
            strbuf_append_mem(json, "false", 5);
        break;
    case LUA_TTABLE:
        current_depth++;
        json_check_encode_depth(l, cfg, current_depth, json);
        len = lua_array_length(l, cfg, json);
        if (len > 0)
            json_append_array(l, cfg, current_depth, json, len);
        else
            json_append_object(l, cfg, current_depth, json);
        break;
    case LUA_TNIL:
        strbuf_append_mem(json, "null", 4);
        break;
    case LUA_TLIGHTUSERDATA:
        if (lua_touserdata(l, -1) == NULL) {
            strbuf_append_mem(json, "null", 4);
            break;
        }
    default:
        /* Remaining types (LUA_TFUNCTION, LUA_TUSERDATA, LUA_TTHREAD,
         * and LUA_TLIGHTUSERDATA) cannot be serialised */
        json_encode_exception(l, cfg, json, -1, "type not supported");
        /* never returns */
    }
}