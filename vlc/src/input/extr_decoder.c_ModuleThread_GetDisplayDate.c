#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct decoder_owner {float output_rate; int /*<<< orphan*/  p_clock; int /*<<< orphan*/  lock; scalar_t__ paused; scalar_t__ b_waiting; } ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_clock_ConvertToSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_tick_t ModuleThread_GetDisplayDate( decoder_t *p_dec,
                                       vlc_tick_t system_now, vlc_tick_t i_ts )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );

    vlc_mutex_lock( &p_owner->lock );
    if( p_owner->b_waiting || p_owner->paused )
        i_ts = VLC_TICK_INVALID;
    float rate = p_owner->output_rate;
    vlc_mutex_unlock( &p_owner->lock );

    if( !p_owner->p_clock || i_ts == VLC_TICK_INVALID )
        return i_ts;

    return vlc_clock_ConvertToSystem( p_owner->p_clock, system_now, i_ts, rate );
}