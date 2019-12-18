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
typedef  int /*<<< orphan*/  vout_control_t ;
typedef  int /*<<< orphan*/  vout_control_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_control_Push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_cmd_Init (int /*<<< orphan*/ *,int) ; 

void vout_control_PushVoid(vout_control_t *ctrl, int type)
{
    vout_control_cmd_t cmd;

    vout_control_cmd_Init(&cmd, type);
    vout_control_Push(ctrl, &cmd);
}