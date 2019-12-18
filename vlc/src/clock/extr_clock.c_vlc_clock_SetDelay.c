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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_delay ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ vlc_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

vlc_tick_t vlc_clock_SetDelay(vlc_clock_t *clock, vlc_tick_t delay)
{
    return clock->set_delay(clock, delay);
}