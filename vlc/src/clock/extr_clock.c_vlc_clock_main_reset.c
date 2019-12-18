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
struct TYPE_3__ {float coeff; float rate; int /*<<< orphan*/  cond; int /*<<< orphan*/  last; int /*<<< orphan*/  wait_sync_ref; int /*<<< orphan*/  wait_sync_ref_priority; int /*<<< orphan*/  offset; int /*<<< orphan*/  coeff_avg; } ;
typedef  TYPE_1__ vlc_clock_main_t ;

/* Variables and functions */
 int /*<<< orphan*/  AvgReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  clock_point_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_broadcast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_clock_main_reset(vlc_clock_main_t *main_clock)
{
    AvgReset(&main_clock->coeff_avg);
    main_clock->coeff = 1.0f;
    main_clock->rate = 1.0f;
    main_clock->offset = VLC_TICK_INVALID;

    main_clock->wait_sync_ref_priority = UINT_MAX;
    main_clock->wait_sync_ref =
        main_clock->last = clock_point_Create(VLC_TICK_INVALID, VLC_TICK_INVALID);
    vlc_cond_broadcast(&main_clock->cond);
}