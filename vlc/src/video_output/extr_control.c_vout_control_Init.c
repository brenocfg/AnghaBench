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
struct TYPE_3__ {int is_held; int is_waiting; int is_dead; int can_sleep; int /*<<< orphan*/  cmd; int /*<<< orphan*/  wait_available; int /*<<< orphan*/  wait_request; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vout_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

void vout_control_Init(vout_control_t *ctrl)
{
    vlc_mutex_init(&ctrl->lock);
    vlc_cond_init(&ctrl->wait_request);
    vlc_cond_init(&ctrl->wait_available);

    ctrl->is_held = false;
    ctrl->is_waiting = false;
    ctrl->is_dead = false;
    ctrl->can_sleep = true;
    ARRAY_INIT(ctrl->cmd);
}