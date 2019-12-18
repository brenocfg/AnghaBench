#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {scalar_t__ current_depth; scalar_t__ data; scalar_t__ ptr; int /*<<< orphan*/  tmp; TYPE_1__* cfg; } ;
typedef  TYPE_2__ json_parse_t ;
struct TYPE_4__ {scalar_t__ decode_max_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_decode_descend(lua_State *l, json_parse_t *json, int slots)
{
    json->current_depth++;

    if (json->current_depth <= json->cfg->decode_max_depth &&
        lua_checkstack(l, slots)) {
        return;
    }

    strbuf_free(json->tmp);
    luaL_error(l, "Found too many nested data structures (%d) at character %d",
        json->current_depth, json->ptr - json->data);
}