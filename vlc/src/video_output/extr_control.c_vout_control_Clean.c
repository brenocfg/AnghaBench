#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  wait_available; int /*<<< orphan*/  wait_request; int /*<<< orphan*/  lock; TYPE_3__ cmd; } ;
typedef  TYPE_1__ vout_control_t ;
typedef  int /*<<< orphan*/  vout_control_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (TYPE_3__) ; 
 int /*<<< orphan*/  ARRAY_VAL (TYPE_3__,int) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_cmd_Clean (int /*<<< orphan*/ *) ; 

void vout_control_Clean(vout_control_t *ctrl)
{
    /* */
    for (int i = 0; i < ctrl->cmd.i_size; i++) {
        vout_control_cmd_t cmd = ARRAY_VAL(ctrl->cmd, i);
        vout_control_cmd_Clean(&cmd);
    }
    ARRAY_RESET(ctrl->cmd);

    vlc_mutex_destroy(&ctrl->lock);
    vlc_cond_destroy(&ctrl->wait_request);
    vlc_cond_destroy(&ctrl->wait_available);
}