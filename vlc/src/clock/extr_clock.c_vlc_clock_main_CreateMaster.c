#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  rc; int /*<<< orphan*/ * master; } ;
typedef  TYPE_1__ vlc_clock_main_t ;
struct vlc_clock_cbs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_clock_main_Create (TYPE_1__*,int /*<<< orphan*/ ,struct vlc_clock_cbs const*,void*) ; 
 int /*<<< orphan*/  vlc_clock_master_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_clock_set_master_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_clock_set_slave_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_clock_t *vlc_clock_main_CreateMaster(vlc_clock_main_t *main_clock,
                                         const struct vlc_clock_cbs *cbs,
                                         void *cbs_data)
{
    /* The master has always the 0 priority */
    vlc_clock_t *clock = vlc_clock_main_Create(main_clock, 0, cbs, cbs_data);
    if (!clock)
        return NULL;

    vlc_mutex_lock(&main_clock->lock);
    if (main_clock->master != NULL)
    {
        vlc_clock_master_reset(main_clock->master);
        vlc_clock_set_slave_callbacks(main_clock->master);
    }
    vlc_clock_set_master_callbacks(clock);
    main_clock->master = clock;
    main_clock->rc++;
    vlc_mutex_unlock(&main_clock->lock);

    return clock;
}