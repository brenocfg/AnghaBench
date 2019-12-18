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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  encode_buf; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 TYPE_1__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int json_destroy_config(lua_State *l)
{
    json_config_t *cfg;

    cfg = lua_touserdata(l, 1);
    if (cfg)
        strbuf_free(&cfg->encode_buf);
    cfg = NULL;

    return 0;
}