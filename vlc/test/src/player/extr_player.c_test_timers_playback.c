#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_5__ {size_t size; struct report_timer* data; } ;
typedef  TYPE_2__ vec_report_timer ;
struct timer_state {scalar_t__ delay; TYPE_2__ vec; } ;
struct TYPE_4__ {scalar_t__ system_date; scalar_t__ ts; scalar_t__ position; unsigned int rate; scalar_t__ length; } ;
struct report_timer {scalar_t__ type; scalar_t__ discontinuity_date; TYPE_1__ point; } ;
struct media_params {size_t* track_count; unsigned int video_frame_rate; int video_frame_rate_base; scalar_t__ audio_sample_length; } ;
struct ctx {int dummy; } ;

/* Variables and functions */
 size_t AUDIO_ES ; 
 struct media_params DEFAULT_MEDIA_PARAMS (scalar_t__) ; 
 scalar_t__ INT64_MAX ; 
 size_t MAX_UPDATE_COUNT ; 
 size_t REGULAR_DELAY_TIMER_IDX ; 
 size_t REGULAR_TIMER_IDX ; 
 scalar_t__ REPORT_TIMER_DISCONTINUITY ; 
 scalar_t__ REPORT_TIMER_POINT ; 
 scalar_t__ SAMPLE_LENGTH ; 
 size_t SMPTE_TIMER_IDX ; 
 size_t SPU_ES ; 
 size_t TIMER_COUNT ; 
 size_t VIDEO_ES ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STARTED ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,char*,struct media_params*,int) ; 
 int /*<<< orphan*/  player_set_rate (struct ctx*,unsigned int) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_timers_assert_smpte (struct timer_state*,scalar_t__,unsigned int,int,int) ; 
 int /*<<< orphan*/  vlc_vector_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_timers_playback(struct ctx *ctx, struct timer_state timers[],
                     size_t track_count, vlc_tick_t length, unsigned fps,
                     unsigned rate)
{
#define SAMPLE_LENGTH VLC_TICK_FROM_MS(1)
#define MAX_UPDATE_COUNT (size_t)(length / SAMPLE_LENGTH)

    struct media_params params = DEFAULT_MEDIA_PARAMS(length);

    params.track_count[VIDEO_ES] = track_count;
    params.track_count[AUDIO_ES] = track_count;
    params.track_count[SPU_ES] = track_count;
    params.audio_sample_length = SAMPLE_LENGTH;
    params.video_frame_rate = fps;
    params.video_frame_rate_base = 1;

    player_set_current_mock_media(ctx, "media1", &params, false);
    player_set_rate(ctx, rate);
    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STARTED);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);

    /* Common for regular timers */
    for (size_t timer_idx = 0; timer_idx < SMPTE_TIMER_IDX; ++timer_idx)
    {
        struct timer_state *timer = &timers[timer_idx];
        vec_report_timer *vec = &timer->vec;

        for (size_t i = 1; i < vec->size; ++i)
        {
            struct report_timer *prev_report = &vec->data[i - 1];
            struct report_timer *report = &vec->data[i];

            /* Only the last event should be a discontinuity. We can assume
             * that since we are not seeking and playing a fake content */
            if (i < vec->size - 1)
            {
                if (i == 1)
                    assert(prev_report->point.system_date == INT64_MAX);

                assert(report->type == REPORT_TIMER_POINT);
                /* ts/position should increase, rate should stay to 1.f */
                assert(report->point.ts >= prev_report->point.ts);
                assert(report->point.system_date != VLC_TICK_INVALID);
                assert(report->point.position >= prev_report->point.position);
                assert(report->point.rate == rate);
                assert(report->point.length == length);
            }
            else
            {
                assert(report->type == REPORT_TIMER_DISCONTINUITY);
                assert(report->discontinuity_date == VLC_TICK_INVALID);
            }
        }
    }

    /* Assertions for the regular timer that received all update points */
    if (track_count != 0)
    {
        struct timer_state *timer = &timers[REGULAR_TIMER_IDX];
        vec_report_timer *vec = &timer->vec;

        /* Check that we didn't miss any update points */
        assert(vec->size > 1);
        size_t point_count = 1;
        for (size_t i = 1; i < vec->size - 1; ++i)
        {
            struct report_timer *prev_report = &vec->data[i - 1];
            struct report_timer *report = &vec->data[i];

            /* Don't count forced points */
            if (report->point.ts != prev_report->point.ts)
            {
                assert(report->point.ts == prev_report->point.ts + SAMPLE_LENGTH);
                point_count++;
            }
        }
        assert(vec->data[vec->size - 2].point.ts
               == length - SAMPLE_LENGTH + VLC_TICK_0);
        assert(point_count == MAX_UPDATE_COUNT);
    }

    /* Assertions for the regular filtered timer */
    {
        struct timer_state *timer = &timers[REGULAR_DELAY_TIMER_IDX];
        vec_report_timer *vec = &timer->vec;

        /* It should not receive all update points */
        assert(vec->size < MAX_UPDATE_COUNT);

        for (size_t i = 1; i < vec->size; ++i)
        {
            struct report_timer *prev_report = &vec->data[i - 1];
            struct report_timer *report = &vec->data[i];
            if (i < vec->size - 1)
            {
                if (i == 1)
                    assert(prev_report->point.system_date == INT64_MAX);
                else
                    assert(report->point.system_date - prev_report->point.system_date
                           >= timer->delay);
            }
        }
    }

    if (track_count > 0)
        test_timers_assert_smpte(&timers[SMPTE_TIMER_IDX], length, fps, false, 3);
    else
    {
        struct timer_state *timer = &timers[SMPTE_TIMER_IDX];
        vec_report_timer *vec = &timer->vec;
        assert(vec->size == 0);
    }
    test_end(ctx);

    for (size_t i = 0; i < TIMER_COUNT; ++i)
    {
        struct timer_state *timer = &timers[i];
        vlc_vector_clear(&timer->vec);
    }
}