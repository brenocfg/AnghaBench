#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* msi_call; } ;
typedef  TYPE_2__ ToxAVCall ;
struct TYPE_9__ {int /*<<< orphan*/  second; int /*<<< orphan*/  (* first ) (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; TYPE_1__ ccb; } ;
typedef  TYPE_3__ ToxAV ;
struct TYPE_12__ {int peer_capabilities; int /*<<< orphan*/  friend_number; TYPE_2__* av_call; } ;
typedef  TYPE_4__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  LOGGER_WARNING (char*) ; 
 TYPE_2__* call_new (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msi_CapSAudio ; 
 int msi_CapSVideo ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int callback_invite(void *toxav_inst, MSICall *call)
{
    ToxAV *toxav = toxav_inst;
    pthread_mutex_lock(toxav->mutex);

    ToxAVCall *av_call = call_new(toxav, call->friend_number, NULL);

    if (av_call == NULL) {
        LOGGER_WARNING("Failed to initialize call...");
        pthread_mutex_unlock(toxav->mutex);
        return -1;
    }

    call->av_call = av_call;
    av_call->msi_call = call;

    if (toxav->ccb.first)
        toxav->ccb.first(toxav, call->friend_number, call->peer_capabilities & msi_CapSAudio,
                         call->peer_capabilities & msi_CapSVideo, toxav->ccb.second);
    else {
        /* No handler to capture the call request, send failure */
        pthread_mutex_unlock(toxav->mutex);
        return -1;
    }

    pthread_mutex_unlock(toxav->mutex);
    return 0;
}