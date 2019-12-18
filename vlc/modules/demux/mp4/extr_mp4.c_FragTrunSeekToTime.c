#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ stime_t ;
struct TYPE_13__ {int i_count; unsigned int i_current; TYPE_7__* p_array; } ;
struct TYPE_14__ {scalar_t__ i_default_sample_duration; scalar_t__ i_default_sample_size; unsigned int i_trun_sample; TYPE_4__ runs; scalar_t__ i_trun_sample_pos; } ;
struct TYPE_15__ {TYPE_5__ context; int /*<<< orphan*/  b_ok; } ;
typedef  TYPE_6__ mp4_track_t ;
struct TYPE_16__ {scalar_t__ i_offset; scalar_t__ i_first_dts; TYPE_2__* p_trun; } ;
typedef  TYPE_7__ mp4_run_t ;
struct TYPE_17__ {unsigned int i_sample_count; int i_flags; TYPE_3__* p_samples; } ;
struct TYPE_12__ {scalar_t__ i_duration; scalar_t__ i_size; } ;
struct TYPE_10__ {TYPE_8__* p_trun; } ;
struct TYPE_11__ {TYPE_1__ data; } ;
typedef  TYPE_8__ MP4_Box_data_trun_t ;

/* Variables and functions */
 int MP4_TRUN_SAMPLE_DURATION ; 
 int MP4_TRUN_SAMPLE_SIZE ; 

__attribute__((used)) static void FragTrunSeekToTime( mp4_track_t *p_track, stime_t i_target_time )
{
    if( !p_track->b_ok || p_track->context.runs.i_count < 1 )
        return;

    unsigned i_run = 0;
    unsigned i_sample = 0;
    uint64_t i_pos = p_track->context.runs.p_array[0].i_offset;
    stime_t  i_time = p_track->context.runs.p_array[0].i_first_dts;

    for( unsigned r = 0; r < p_track->context.runs.i_count; r++ )
    {
        const mp4_run_t *p_run = &p_track->context.runs.p_array[r];
        const MP4_Box_data_trun_t *p_data =
                    p_track->context.runs.p_array[r].p_trun->data.p_trun;
        if( i_time > i_target_time )
            break;

        i_run = r;
        i_time = p_run->i_first_dts;
        i_pos = p_run->i_offset;
        i_sample = 0;

        uint32_t dur = p_track->context.i_default_sample_duration;
        uint32_t len = p_track->context.i_default_sample_size;
        for ( unsigned i=0; i<p_data->i_sample_count; i++ )
        {
            if( p_data->i_flags & MP4_TRUN_SAMPLE_DURATION )
                dur = p_data->p_samples[i].i_duration;

            /* check condition */
            if( i_time + dur > i_target_time )
                break;

            if( p_data->i_flags & MP4_TRUN_SAMPLE_SIZE )
                len = p_data->p_samples[i].i_size;

            i_time += dur;
            i_pos += len;
        }
    }

    p_track->context.i_trun_sample = i_sample;
    p_track->context.i_trun_sample_pos = i_pos;
    p_track->context.runs.i_current = i_run;
}