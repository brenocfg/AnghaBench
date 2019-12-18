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
struct TYPE_5__ {scalar_t__* pi_value; scalar_t__ i_index; } ;
struct TYPE_6__ {int b_has_reference; int b_has_external_clock; float rate; int b_paused; void* i_pause_date; scalar_t__ i_pts_delay; TYPE_1__ late; int /*<<< orphan*/  drift; void* i_next_drift_update; scalar_t__ i_buffering_duration; void* i_ts_max; void* last; void* ref; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ input_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  AvgInit (int /*<<< orphan*/ *,int) ; 
 int INPUT_CLOCK_LATE_COUNT ; 
 void* VLC_TICK_INVALID ; 
 void* clock_point_Create (void*,void*) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

input_clock_t *input_clock_New( float rate )
{
    input_clock_t *cl = malloc( sizeof(*cl) );
    if( !cl )
        return NULL;

    vlc_mutex_init( &cl->lock );
    cl->b_has_reference = false;
    cl->ref = clock_point_Create( VLC_TICK_INVALID, VLC_TICK_INVALID );
    cl->b_has_external_clock = false;

    cl->last = clock_point_Create( VLC_TICK_INVALID, VLC_TICK_INVALID );

    cl->i_ts_max = VLC_TICK_INVALID;

    cl->i_buffering_duration = 0;

    cl->i_next_drift_update = VLC_TICK_INVALID;
    AvgInit( &cl->drift, 10 );

    cl->late.i_index = 0;
    for( int i = 0; i < INPUT_CLOCK_LATE_COUNT; i++ )
        cl->late.pi_value[i] = 0;

    cl->rate = rate;
    cl->i_pts_delay = 0;
    cl->b_paused = false;
    cl->i_pause_date = VLC_TICK_INVALID;

    return cl;
}