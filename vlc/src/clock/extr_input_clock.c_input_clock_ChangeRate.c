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
typedef  float vlc_tick_t ;
struct TYPE_5__ {float system; } ;
struct TYPE_6__ {float system; } ;
struct TYPE_7__ {float rate; int /*<<< orphan*/  lock; TYPE_1__ ref; TYPE_2__ last; scalar_t__ b_has_reference; } ;
typedef  TYPE_3__ input_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_clock_ChangeRate( input_clock_t *cl, float rate )
{
    vlc_mutex_lock( &cl->lock );

    if( cl->b_has_reference )
    {
        /* Move the reference point (as if we were playing at the new rate
         * from the start */
        cl->ref.system = cl->last.system - (vlc_tick_t) ((cl->last.system - cl->ref.system) / rate * cl->rate);
    }
    cl->rate = rate;

    vlc_mutex_unlock( &cl->lock );
}