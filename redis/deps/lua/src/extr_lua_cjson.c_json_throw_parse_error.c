#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {char* string; } ;
struct TYPE_7__ {size_t type; scalar_t__ index; TYPE_1__ value; } ;
typedef  TYPE_2__ json_token_t ;
struct TYPE_8__ {int /*<<< orphan*/  tmp; } ;
typedef  TYPE_3__ json_parse_t ;

/* Variables and functions */
 size_t T_ERROR ; 
 char** json_token_type_name ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_throw_parse_error(lua_State *l, json_parse_t *json,
                                   const char *exp, json_token_t *token)
{
    const char *found;

    strbuf_free(json->tmp);

    if (token->type == T_ERROR)
        found = token->value.string;
    else
        found = json_token_type_name[token->type];

    /* Note: token->index is 0 based, display starting from 1 */
    luaL_error(l, "Expected %s but found %s at character %d",
               exp, found, token->index + 1);
}