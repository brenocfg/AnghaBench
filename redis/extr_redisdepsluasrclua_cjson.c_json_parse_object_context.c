#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  string; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  string_len; TYPE_1__ value; } ;
typedef  TYPE_2__ json_token_t ;
typedef  int /*<<< orphan*/  json_parse_t ;

/* Variables and functions */
 scalar_t__ T_COLON ; 
 scalar_t__ T_COMMA ; 
 scalar_t__ T_OBJ_END ; 
 scalar_t__ T_STRING ; 
 int /*<<< orphan*/  json_decode_ascend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decode_descend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_next_token (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  json_process_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  json_throw_parse_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void json_parse_object_context(lua_State *l, json_parse_t *json)
{
    json_token_t token;

    /* 3 slots required:
     * .., table, key, value */
    json_decode_descend(l, json, 3);

    lua_newtable(l);

    json_next_token(json, &token);

    /* Handle empty objects */
    if (token.type == T_OBJ_END) {
        json_decode_ascend(json);
        return;
    }

    while (1) {
        if (token.type != T_STRING)
            json_throw_parse_error(l, json, "object key string", &token);

        /* Push key */
        lua_pushlstring(l, token.value.string, token.string_len);

        json_next_token(json, &token);
        if (token.type != T_COLON)
            json_throw_parse_error(l, json, "colon", &token);

        /* Fetch value */
        json_next_token(json, &token);
        json_process_value(l, json, &token);

        /* Set key = value */
        lua_rawset(l, -3);

        json_next_token(json, &token);

        if (token.type == T_OBJ_END) {
            json_decode_ascend(json);
            return;
        }

        if (token.type != T_COMMA)
            json_throw_parse_error(l, json, "comma or object end", &token);

        json_next_token(json, &token);
    }
}