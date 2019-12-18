#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ ToxAV ;
struct TYPE_6__ {scalar_t__ av_call; int /*<<< orphan*/  friend_number; } ;
typedef  TYPE_2__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  TOXAV_FRIEND_CALL_STATE_ERROR ; 
 int /*<<< orphan*/  call_kill_transmission (scalar_t__) ; 
 int /*<<< orphan*/  call_remove (scalar_t__) ; 
 int /*<<< orphan*/  invoke_call_state_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 

int callback_error(void *toxav_inst, MSICall *call)
{
    ToxAV *toxav = toxav_inst;
    pthread_mutex_lock(toxav->mutex);

    invoke_call_state_callback(toxav, call->friend_number, TOXAV_FRIEND_CALL_STATE_ERROR);

    if (call->av_call) {
        call_kill_transmission(call->av_call);
        call_remove(call->av_call);
    }

    pthread_mutex_unlock(toxav->mutex);
    return 0;
}