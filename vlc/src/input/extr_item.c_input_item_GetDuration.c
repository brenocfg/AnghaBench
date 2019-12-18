#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {scalar_t__ i_duration; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ input_item_t ;

/* Variables and functions */
 scalar_t__ INPUT_DURATION_INDEFINITE ; 
 scalar_t__ INPUT_DURATION_UNSET ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_tick_t input_item_GetDuration( input_item_t *p_i )
{
    vlc_mutex_lock( &p_i->lock );

    vlc_tick_t i_duration = p_i->i_duration;

    vlc_mutex_unlock( &p_i->lock );
    if (i_duration == INPUT_DURATION_INDEFINITE)
        i_duration = 0;
    else if (i_duration == INPUT_DURATION_UNSET)
        i_duration = 0;
    return i_duration;
}