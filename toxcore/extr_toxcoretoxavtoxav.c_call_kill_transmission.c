#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * second; int /*<<< orphan*/ * first; } ;
struct TYPE_5__ {int /*<<< orphan*/ * second; int /*<<< orphan*/ * first; } ;
struct TYPE_7__ {scalar_t__ active; int /*<<< orphan*/  mutex; int /*<<< orphan*/  mutex_video; int /*<<< orphan*/  mutex_audio; TYPE_2__ video; TYPE_1__ audio; int /*<<< orphan*/  bwc; } ;
typedef  TYPE_3__ ToxAVCall ;

/* Variables and functions */
 int /*<<< orphan*/  ac_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwc_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_kill (int /*<<< orphan*/ *) ; 

void call_kill_transmission(ToxAVCall *call)
{
    if (call == NULL || call->active == 0)
        return;

    call->active = 0;

    pthread_mutex_lock(call->mutex_audio);
    pthread_mutex_unlock(call->mutex_audio);
    pthread_mutex_lock(call->mutex_video);
    pthread_mutex_unlock(call->mutex_video);
    pthread_mutex_lock(call->mutex);
    pthread_mutex_unlock(call->mutex);

    bwc_kill(call->bwc);

    rtp_kill(call->audio.first);
    ac_kill(call->audio.second);
    call->audio.first = NULL;
    call->audio.second = NULL;

    rtp_kill(call->video.first);
    vc_kill(call->video.second);
    call->video.first = NULL;
    call->video.second = NULL;

    pthread_mutex_destroy(call->mutex_audio);
    pthread_mutex_destroy(call->mutex_video);
    pthread_mutex_destroy(call->mutex);
}