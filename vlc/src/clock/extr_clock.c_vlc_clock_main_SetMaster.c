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
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * master; } ;
typedef  TYPE_1__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_clock_master_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_clock_set_master_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_clock_set_slave_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_clock_main_SetMaster(vlc_clock_main_t *main_clock, vlc_clock_t *clock)
{
    vlc_mutex_lock(&main_clock->lock);
    if (main_clock->master != NULL)
    {
        vlc_clock_master_reset(main_clock->master);
        vlc_clock_set_slave_callbacks(main_clock->master);
    }
    vlc_clock_set_master_callbacks(clock);
    main_clock->master = clock;
    vlc_mutex_unlock(&main_clock->lock);
}