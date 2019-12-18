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
struct TYPE_3__ {int encode_keep_buffer; int /*<<< orphan*/  encode_buf; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 TYPE_1__* json_arg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_enum_option (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int json_cfg_encode_keep_buffer(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);
    int old_value;

    old_value = cfg->encode_keep_buffer;

    json_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);

    /* Init / free the buffer if the setting has changed */
    if (old_value ^ cfg->encode_keep_buffer) {
        if (cfg->encode_keep_buffer)
            strbuf_init(&cfg->encode_buf, 0);
        else
            strbuf_free(&cfg->encode_buf);
    }

    return 1;
}