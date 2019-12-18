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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  boolean; int /*<<< orphan*/  number; int /*<<< orphan*/  string; } ;
struct TYPE_6__ {int type; TYPE_1__ value; int /*<<< orphan*/  string_len; } ;
typedef  TYPE_2__ json_token_t ;
typedef  int /*<<< orphan*/  json_parse_t ;

/* Variables and functions */
#define  T_ARR_BEGIN 133 
#define  T_BOOLEAN 132 
#define  T_NULL 131 
#define  T_NUMBER 130 
#define  T_OBJ_BEGIN 129 
#define  T_STRING 128 
 int /*<<< orphan*/  json_parse_array_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_parse_object_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_throw_parse_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_process_value(lua_State *l, json_parse_t *json,
                               json_token_t *token)
{
    switch (token->type) {
    case T_STRING:
        lua_pushlstring(l, token->value.string, token->string_len);
        break;;
    case T_NUMBER:
        lua_pushnumber(l, token->value.number);
        break;;
    case T_BOOLEAN:
        lua_pushboolean(l, token->value.boolean);
        break;;
    case T_OBJ_BEGIN:
        json_parse_object_context(l, json);
        break;;
    case T_ARR_BEGIN:
        json_parse_array_context(l, json);
        break;;
    case T_NULL:
        /* In Lua, setting "t[k] = nil" will delete k from the table.
         * Hence a NULL pointer lightuserdata object is used instead */
        lua_pushlightuserdata(l, NULL);
        break;;
    default:
        json_throw_parse_error(l, json, "value", token);
    }
}