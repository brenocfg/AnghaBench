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
struct TYPE_5__ {TYPE_2__* owner; } ;
typedef  TYPE_1__ vlc_clock_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_sync_ref; int /*<<< orphan*/  wait_sync_ref_priority; } ;
typedef  TYPE_2__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  clock_point_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_clock_on_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_clock_slave_reset(vlc_clock_t *clock)
{
    vlc_clock_main_t *main_clock = clock->owner;
    vlc_mutex_lock(&main_clock->lock);
    main_clock->wait_sync_ref_priority = UINT_MAX;
    main_clock->wait_sync_ref =
        clock_point_Create(VLC_TICK_INVALID, VLC_TICK_INVALID);

    vlc_mutex_unlock(&main_clock->lock);

    vlc_clock_on_update(clock, VLC_TICK_INVALID, VLC_TICK_INVALID, 1.0f, 0, 0);
}