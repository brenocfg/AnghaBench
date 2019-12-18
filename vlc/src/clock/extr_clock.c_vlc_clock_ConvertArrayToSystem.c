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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* to_system_locked ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ;TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_clock_ConvertArrayToSystem(vlc_clock_t *clock, vlc_tick_t system_now,
                                    vlc_tick_t *ts_array, size_t ts_count,
                                    double rate)
{
    vlc_clock_main_t *main_clock = clock->owner;
    vlc_mutex_lock(&main_clock->lock);
    for (size_t i = 0; i < ts_count; ++i)
        ts_array[i] = clock->to_system_locked(clock, system_now, ts_array[i],
                                              rate);
    vlc_mutex_unlock(&main_clock->lock);
}