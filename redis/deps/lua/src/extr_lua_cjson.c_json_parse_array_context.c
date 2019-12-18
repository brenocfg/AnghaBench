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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ json_token_t ;
typedef  int /*<<< orphan*/  json_parse_t ;

/* Variables and functions */
 scalar_t__ T_ARR_END ; 
 scalar_t__ T_COMMA ; 
 int /*<<< orphan*/  json_decode_ascend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decode_descend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_next_token (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  json_process_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  json_throw_parse_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void json_parse_array_context(lua_State *l, json_parse_t *json)
{
    json_token_t token;
    int i;

    /* 2 slots required:
     * .., table, value */
    json_decode_descend(l, json, 2);

    lua_newtable(l);

    json_next_token(json, &token);

    /* Handle empty arrays */
    if (token.type == T_ARR_END) {
        json_decode_ascend(json);
        return;
    }

    for (i = 1; ; i++) {
        json_process_value(l, json, &token);
        lua_rawseti(l, -2, i);            /* arr[i] = value */

        json_next_token(json, &token);

        if (token.type == T_ARR_END) {
            json_decode_ascend(json);
            return;
        }

        if (token.type != T_COMMA)
            json_throw_parse_error(l, json, "comma or array end", &token);

        json_next_token(json, &token);
    }
}