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
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_6__ {scalar_t__ system; scalar_t__ stream; } ;
struct TYPE_5__ {scalar_t__ system; scalar_t__ stream; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__ ref; TYPE_1__ last; int /*<<< orphan*/  b_has_reference; } ;
typedef  TYPE_3__ input_clock_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int input_clock_GetState( input_clock_t *cl,
                          vlc_tick_t *pi_stream_start, vlc_tick_t *pi_system_start,
                          vlc_tick_t *pi_stream_duration, vlc_tick_t *pi_system_duration )
{
    vlc_mutex_lock( &cl->lock );

    if( !cl->b_has_reference )
    {
        vlc_mutex_unlock( &cl->lock );
        return VLC_EGENERIC;
    }

    *pi_stream_start = cl->ref.stream;
    *pi_system_start = cl->ref.system;

    *pi_stream_duration = cl->last.stream - cl->ref.stream;
    *pi_system_duration = cl->last.system - cl->ref.system;

    vlc_mutex_unlock( &cl->lock );

    return VLC_SUCCESS;
}