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
struct TYPE_6__ {scalar_t__ i_size; } ;
struct TYPE_5__ {int can_sleep; int is_waiting; int /*<<< orphan*/  lock; TYPE_3__ cmd; int /*<<< orphan*/  wait_available; scalar_t__ is_held; int /*<<< orphan*/  wait_request; } ;
typedef  TYPE_1__ vout_control_t ;
typedef  int /*<<< orphan*/  vout_control_cmd_t ;
typedef  scalar_t__ vlc_tick_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REMOVE (TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_VAL (TYPE_3__,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int vout_control_Pop(vout_control_t *ctrl, vout_control_cmd_t *cmd,
                     vlc_tick_t deadline)
{
    vlc_mutex_lock(&ctrl->lock);
    mutex_cleanup_push(&ctrl->lock);

    if (ctrl->cmd.i_size <= 0) {
        /* Spurious wakeups are perfectly fine */
        if (deadline != VLC_TICK_INVALID && ctrl->can_sleep) {
            ctrl->is_waiting = true;
            vlc_cond_signal(&ctrl->wait_available);
            vlc_cond_timedwait(&ctrl->wait_request, &ctrl->lock, deadline);
            ctrl->is_waiting = false;
        }
    }

    while (ctrl->is_held)
        vlc_cond_wait(&ctrl->wait_available, &ctrl->lock);
    vlc_cleanup_pop();

    bool has_cmd;
    if (ctrl->cmd.i_size > 0) {
        has_cmd = true;
        *cmd = ARRAY_VAL(ctrl->cmd, 0);
        ARRAY_REMOVE(ctrl->cmd, 0);
    } else {
        has_cmd = false;
        ctrl->can_sleep = true;
    }
    vlc_mutex_unlock(&ctrl->lock);

    return has_cmd ? VLC_SUCCESS : VLC_EGENERIC;
}