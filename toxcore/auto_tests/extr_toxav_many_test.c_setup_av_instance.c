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
typedef  int /*<<< orphan*/  ToxAV ;
typedef  int /*<<< orphan*/  Tox ;
typedef  scalar_t__ TOXAV_ERR_NEW ;
typedef  int /*<<< orphan*/  CallControl ;

/* Variables and functions */
 scalar_t__ TOXAV_ERR_NEW_OK ; 
 int /*<<< orphan*/  ck_assert (int) ; 
 int /*<<< orphan*/  t_toxav_call_cb ; 
 int /*<<< orphan*/  t_toxav_call_state_cb ; 
 int /*<<< orphan*/  t_toxav_receive_audio_frame_cb ; 
 int /*<<< orphan*/  t_toxav_receive_video_frame_cb ; 
 int /*<<< orphan*/  toxav_callback_audio_receive_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_callback_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_callback_call_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_callback_video_receive_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * toxav_new (int /*<<< orphan*/ *,scalar_t__*) ; 

ToxAV *setup_av_instance(Tox *tox, CallControl *CC)
{
    TOXAV_ERR_NEW error;

    ToxAV *av = toxav_new(tox, &error);
    ck_assert(error == TOXAV_ERR_NEW_OK);

    toxav_callback_call(av, t_toxav_call_cb, CC);
    toxav_callback_call_state(av, t_toxav_call_state_cb, CC);
    toxav_callback_video_receive_frame(av, t_toxav_receive_video_frame_cb, CC);
    toxav_callback_audio_receive_frame(av, t_toxav_receive_audio_frame_cb, CC);

    return av;
}