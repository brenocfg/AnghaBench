#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_control_t ;
struct TYPE_4__ {int boolean; } ;
typedef  TYPE_1__ vout_control_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_control_Push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vout_control_cmd_Init (TYPE_1__*,int) ; 

void vout_control_PushBool(vout_control_t *ctrl, int type, bool boolean)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    cmd.boolean = boolean;
    vout_control_Push(ctrl, &cmd);
}