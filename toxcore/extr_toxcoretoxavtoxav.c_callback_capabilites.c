#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  first; } ;
struct TYPE_8__ {int /*<<< orphan*/  first; } ;
struct TYPE_10__ {TYPE_2__ video; TYPE_1__ audio; } ;
typedef  TYPE_3__ ToxAVCall ;
struct TYPE_11__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_4__ ToxAV ;
struct TYPE_12__ {int peer_capabilities; int /*<<< orphan*/  friend_number; scalar_t__ av_call; } ;
typedef  TYPE_5__ MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  invoke_call_state_callback (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int msi_CapSAudio ; 
 int msi_CapSVideo ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_allow_receiving (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_stop_receiving (int /*<<< orphan*/ ) ; 

int callback_capabilites(void *toxav_inst, MSICall *call)
{
    ToxAV *toxav = toxav_inst;
    pthread_mutex_lock(toxav->mutex);

    if (call->peer_capabilities & msi_CapSAudio)
        rtp_allow_receiving(((ToxAVCall *)call->av_call)->audio.first);
    else
        rtp_stop_receiving(((ToxAVCall *)call->av_call)->audio.first);

    if (call->peer_capabilities & msi_CapSVideo)
        rtp_allow_receiving(((ToxAVCall *)call->av_call)->video.first);
    else
        rtp_stop_receiving(((ToxAVCall *)call->av_call)->video.first);

    invoke_call_state_callback(toxav, call->friend_number, call->peer_capabilities);

    pthread_mutex_unlock(toxav->mutex);
    return 0;
}