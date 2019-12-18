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
struct TYPE_6__ {int /*<<< orphan*/  system; } ;
struct TYPE_5__ {int /*<<< orphan*/  system; } ;
struct TYPE_7__ {int b_paused; scalar_t__ i_pause_date; int /*<<< orphan*/  lock; TYPE_2__ last; TYPE_1__ ref; scalar_t__ b_has_reference; } ;
typedef  TYPE_3__ input_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_clock_ChangePause( input_clock_t *cl, bool b_paused, vlc_tick_t i_date )
{
    vlc_mutex_lock( &cl->lock );
    assert( (!cl->b_paused) != (!b_paused) );

    if( cl->b_paused )
    {
        const vlc_tick_t i_duration = i_date - cl->i_pause_date;

        if( cl->b_has_reference && i_duration > 0 )
        {
            cl->ref.system += i_duration;
            cl->last.system += i_duration;
        }
    }
    cl->i_pause_date = i_date;
    cl->b_paused = b_paused;

    vlc_mutex_unlock( &cl->lock );
}