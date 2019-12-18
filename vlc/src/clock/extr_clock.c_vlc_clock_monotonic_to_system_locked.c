#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  double vlc_tick_t ;
struct TYPE_7__ {scalar_t__ priority; TYPE_3__* owner; } ;
typedef  TYPE_2__ vlc_clock_t ;
struct TYPE_9__ {double stream; double system; } ;
struct TYPE_6__ {scalar_t__ system; double stream; } ;
struct TYPE_8__ {scalar_t__ wait_sync_ref_priority; double const input_dejitter; TYPE_5__ wait_sync_ref; int /*<<< orphan*/  output_dejitter; TYPE_1__ first_pcr; } ;
typedef  TYPE_3__ vlc_clock_main_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 double __MAX (double const,int /*<<< orphan*/ ) ; 
 TYPE_5__ clock_point_Create (double,double) ; 

__attribute__((used)) static vlc_tick_t
vlc_clock_monotonic_to_system_locked(vlc_clock_t *clock, vlc_tick_t now,
                                     vlc_tick_t ts, double rate)
{
    vlc_clock_main_t *main_clock = clock->owner;

    if (clock->priority < main_clock->wait_sync_ref_priority)
    {
        /* XXX: This input_delay calculation is needed until we (finally) get
         * ride of the input clock. This code is adapted from input_clock.c and
         * is used to introduce the same delay than the input clock (first PTS
         * - first PCR). */
        const vlc_tick_t pcr_delay =
            main_clock->first_pcr.system == VLC_TICK_INVALID ? 0 :
            (ts - main_clock->first_pcr.stream) / rate +
            main_clock->first_pcr.system - now;

        const vlc_tick_t input_delay = main_clock->input_dejitter + pcr_delay;

        const vlc_tick_t delay =
            __MAX(input_delay, main_clock->output_dejitter);

        main_clock->wait_sync_ref_priority = clock->priority;
        main_clock->wait_sync_ref = clock_point_Create(now + delay, ts);
    }
    return (ts - main_clock->wait_sync_ref.stream) / rate
        + main_clock->wait_sync_ref.system;
}