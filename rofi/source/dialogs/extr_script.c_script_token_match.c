#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rofi_int_matcher ;
struct TYPE_7__ {TYPE_2__* private_data; } ;
struct TYPE_6__ {TYPE_1__* cmd_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ ScriptModePrivateData ;
typedef  TYPE_3__ Mode ;

/* Variables and functions */
 int helper_token_match (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_token_match ( const Mode *sw, rofi_int_matcher **tokens, unsigned int index )
{
    ScriptModePrivateData *rmpd = sw->private_data;
    return helper_token_match ( tokens, rmpd->cmd_list[index].entry );
}