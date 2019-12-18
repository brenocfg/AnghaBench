#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_y ;
typedef  int /*<<< orphan*/  video_v ;
typedef  int /*<<< orphan*/  video_u ;
struct TYPE_10__ {int /*<<< orphan*/  incoming; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int time_t ;
struct TYPE_11__ {int /*<<< orphan*/  friend_number; TYPE_1__* BobCC; TYPE_1__* AliceCC; int /*<<< orphan*/ * BobAV; int /*<<< orphan*/ * AliceAV; } ;
typedef  TYPE_2__ thread_data ;
typedef  TYPE_1__ int16_t ;
typedef  int /*<<< orphan*/  ToxAV ;
typedef  scalar_t__ TOXAV_ERR_CALL_CONTROL ;
typedef  scalar_t__ TOXAV_ERR_CALL ;
typedef  scalar_t__ TOXAV_ERR_ANSWER ;
typedef  int /*<<< orphan*/  PCM ;
typedef  TYPE_1__ CallControl ;

/* Variables and functions */
 int /*<<< orphan*/  TOXAV_CALL_CONTROL_CANCEL ; 
 scalar_t__ TOXAV_ERR_ANSWER_OK ; 
 scalar_t__ TOXAV_ERR_CALL_CONTROL_OK ; 
 scalar_t__ TOXAV_ERR_CALL_OK ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 int /*<<< orphan*/  ck_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  toxav_audio_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 int /*<<< orphan*/  toxav_call_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  toxav_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_video_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

void *call_thread(void *pd)
{
    ToxAV *AliceAV = ((thread_data *) pd)->AliceAV;
    ToxAV *BobAV = ((thread_data *) pd)->BobAV;
    CallControl *AliceCC = ((thread_data *) pd)->AliceCC;
    CallControl *BobCC = ((thread_data *) pd)->BobCC;
    uint32_t friend_number = ((thread_data *) pd)->friend_number;


    memset(AliceCC, 0, sizeof(CallControl));
    memset(BobCC, 0, sizeof(CallControl));

    { /* Call */
        TOXAV_ERR_CALL rc;
        toxav_call(AliceAV, friend_number, 48, 3000, &rc);

        if (rc != TOXAV_ERR_CALL_OK) {
            printf("toxav_call failed: %d\n", rc);
            ck_assert(0);
        }
    }

    while (!BobCC->incoming)
        c_sleep(10);

    { /* Answer */
        TOXAV_ERR_ANSWER rc;
        toxav_answer(BobAV, 0, 8, 500, &rc);

        if (rc != TOXAV_ERR_ANSWER_OK) {
            printf("toxav_answer failed: %d\n", rc);
            ck_assert(0);
        }
    }

    c_sleep(30);

    int16_t PCM[960];
    uint8_t video_y[800 * 600];
    uint8_t video_u[800 * 600 / 2];
    uint8_t video_v[800 * 600 / 2];

    memset(PCM, 0, sizeof(PCM));
    memset(video_y, 0, sizeof(video_y));
    memset(video_u, 0, sizeof(video_u));
    memset(video_v, 0, sizeof(video_v));

    time_t start_time = time(NULL);

    while (time(NULL) - start_time < 4) {
        toxav_iterate(AliceAV);
        toxav_iterate(BobAV);

        toxav_audio_send_frame(AliceAV, friend_number, PCM, 960, 1, 48000, NULL);
        toxav_audio_send_frame(BobAV, 0, PCM, 960, 1, 48000, NULL);

        toxav_video_send_frame(AliceAV, friend_number, 800, 600, video_y, video_u, video_v, NULL);
        toxav_video_send_frame(BobAV, 0, 800, 600, video_y, video_u, video_v, NULL);

        c_sleep(10);
    }

    { /* Hangup */
        TOXAV_ERR_CALL_CONTROL rc;
        toxav_call_control(AliceAV, friend_number, TOXAV_CALL_CONTROL_CANCEL, &rc);

        if (rc != TOXAV_ERR_CALL_CONTROL_OK) {
            printf("toxav_call_control failed: %d %p %p\n", rc, AliceAV, BobAV);
        }
    }

    c_sleep(30);

    printf ("Closing thread\n");
    pthread_exit(NULL);
}