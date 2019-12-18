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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_request; int /*<<< orphan*/  cmd; int /*<<< orphan*/  is_dead; } ;
typedef  TYPE_1__ vout_control_t ;
typedef  int /*<<< orphan*/  vout_control_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_cmd_Clean (int /*<<< orphan*/ *) ; 

void vout_control_Push(vout_control_t *ctrl, vout_control_cmd_t *cmd)
{
    vlc_mutex_lock(&ctrl->lock);
    if (!ctrl->is_dead) {
        ARRAY_APPEND(ctrl->cmd, *cmd);
        vlc_cond_signal(&ctrl->wait_request);
    } else {
        vout_control_cmd_Clean(cmd);
    }
    vlc_mutex_unlock(&ctrl->lock);
}