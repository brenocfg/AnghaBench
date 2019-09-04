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
struct TYPE_3__ {int /*<<< orphan*/  encode_invalid_numbers; int /*<<< orphan*/  decode_invalid_numbers; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 TYPE_1__* json_arg_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_enum_option (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  json_verify_invalid_number_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int json_cfg_decode_invalid_numbers(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    json_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);

    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}