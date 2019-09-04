#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ToxAVCall ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ ToxAV ;
struct TYPE_8__ {int /*<<< orphan*/  peer_capabilities; int /*<<< orphan*/  friend_number; } ;
typedef  TYPE_2__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/ * call_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_prepare_transmission (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callback_error (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  invoke_call_state_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 

int callback_start(void *toxav_inst, MSICall *call)
{
    ToxAV *toxav = toxav_inst;
    pthread_mutex_lock(toxav->mutex);

    ToxAVCall *av_call = call_get(toxav, call->friend_number);

    if (av_call == NULL) {
        /* Should this ever happen? */
        pthread_mutex_unlock(toxav->mutex);
        return -1;
    }

    if (!call_prepare_transmission(av_call)) {
        callback_error(toxav_inst, call);
        pthread_mutex_unlock(toxav->mutex);
        return -1;
    }

    if (!invoke_call_state_callback(toxav, call->friend_number, call->peer_capabilities)) {
        callback_error(toxav_inst, call);
        pthread_mutex_unlock(toxav->mutex);
        return -1;
    }

    pthread_mutex_unlock(toxav->mutex);
    return 0;
}