#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_6__ {scalar_t__ (* to_system_locked ) (TYPE_1__*,scalar_t__,scalar_t__,double) ;TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__,scalar_t__,double) ; 
 int /*<<< orphan*/  vlc_clock_on_update (TYPE_1__*,scalar_t__,scalar_t__,double,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_tick_t vlc_clock_slave_update(vlc_clock_t *clock,
                                         vlc_tick_t system_now,
                                         vlc_tick_t ts, double rate,
                                         unsigned frame_rate,
                                         unsigned frame_rate_base)
{
    vlc_clock_main_t *main_clock = clock->owner;
    vlc_mutex_lock(&main_clock->lock);

    /* If system_now is INT64_MAX, the update is forced, don't modify anything
     * but only notify the new clock point. */
    vlc_tick_t computed = system_now == INT64_MAX ? INT64_MAX
                        : clock->to_system_locked(clock, system_now, ts, rate);

    vlc_mutex_unlock(&main_clock->lock);

    vlc_clock_on_update(clock, computed, ts, rate, frame_rate, frame_rate_base);
    return computed != INT64_MAX ? computed - system_now : INT64_MAX;
}