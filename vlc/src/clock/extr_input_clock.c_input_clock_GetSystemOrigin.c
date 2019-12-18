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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {int /*<<< orphan*/  system; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  i_pts_delay; TYPE_1__ ref; int /*<<< orphan*/  b_has_reference; } ;
typedef  TYPE_2__ input_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_clock_GetSystemOrigin( input_clock_t *cl, vlc_tick_t *pi_system, vlc_tick_t *pi_delay )
{
    vlc_mutex_lock( &cl->lock );

    assert( cl->b_has_reference );

    *pi_system = cl->ref.system;
    if( pi_delay )
        *pi_delay  = cl->i_pts_delay;

    vlc_mutex_unlock( &cl->lock );
}