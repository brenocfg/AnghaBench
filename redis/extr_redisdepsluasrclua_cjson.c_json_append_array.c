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
 int /*<<< orphan*/  json_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  strbuf_append_char (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void json_append_array(lua_State *l, json_config_t *cfg, int current_depth,
                              strbuf_t *json, int array_length)
{
    int comma, i;

    strbuf_append_char(json, '[');

    comma = 0;
    for (i = 1; i <= array_length; i++) {
        if (comma)
            strbuf_append_char(json, ',');
        else
            comma = 1;

        lua_rawgeti(l, -1, i);
        json_append_data(l, cfg, current_depth, json);
        lua_pop(l, 1);
    }

    strbuf_append_char(json, ']');
}