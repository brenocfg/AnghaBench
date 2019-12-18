#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
struct test_ctx {size_t test_idx; int b_done; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;
struct TYPE_5__ {scalar_t__ i_chroma; } ;
struct TYPE_6__ {int date; TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_7__ {int b_use_pos; int f_pos; int i_add_video_track_at; int i_time; scalar_t__ b_expected_success; } ;

/* Variables and functions */
 int MOCK_DURATION ; 
 scalar_t__ VLC_CODEC_ARGB ; 
 int VLC_TICK_0 ; 
 int VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* test_params ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thumbnailer_callback( void* data, picture_t* thumbnail )
{
    struct test_ctx* p_ctx = data;
    vlc_mutex_lock( &p_ctx->lock );

    if ( thumbnail != NULL )
    {
        assert( test_params[p_ctx->test_idx].b_expected_success &&
                "Expected failure but got a thumbnail" );
        assert( thumbnail->format.i_chroma == VLC_CODEC_ARGB );

        /* TODO: Enable this once the new clock is merged */
#if 0
        vlc_tick_t expected_date;
        /* Don't rely on the expected date if it was purposely invalid */
        if ( test_params[p_ctx->test_idx].b_use_pos == true )
            expected_date = MOCK_DURATION * test_params[p_ctx->test_idx].f_pos;
        else if ( test_params[p_ctx->test_idx].i_add_video_track_at != VLC_TICK_INVALID )
            expected_date = test_params[p_ctx->test_idx].i_add_video_track_at;
        else
        {
            if ( test_params[p_ctx->test_idx].i_time < 0 )
                expected_date = VLC_TICK_0;
            else
                expected_date = test_params[p_ctx->test_idx].i_time;
        }
        assert( thumbnail->date == expected_date && "Unexpected picture date");
#endif
    }
    else
        assert( !test_params[p_ctx->test_idx].b_expected_success &&
                "Expected a thumbnail but got a failure" );

    p_ctx->b_done = true;
    vlc_cond_signal( &p_ctx->cond );
    vlc_mutex_unlock( &p_ctx->lock );
}