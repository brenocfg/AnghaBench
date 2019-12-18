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
struct TYPE_3__ {int type; int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ vout_control_cmd_t ;

/* Variables and functions */
#define  VOUT_CONTROL_CHANGE_FILTERS 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void vout_control_cmd_Clean(vout_control_cmd_t *cmd)
{
    switch (cmd->type) {
    case VOUT_CONTROL_CHANGE_FILTERS:
        free(cmd->string);
        break;
    default:
        break;
    }
}