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
struct TYPE_3__ {int /*<<< orphan*/  to_system_locked; int /*<<< orphan*/  set_dejitter; int /*<<< orphan*/  set_delay; int /*<<< orphan*/  reset; int /*<<< orphan*/  update; } ;
typedef  TYPE_1__ vlc_clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_clock_slave_reset ; 
 int /*<<< orphan*/  vlc_clock_slave_set_dejitter ; 
 int /*<<< orphan*/  vlc_clock_slave_set_delay ; 
 int /*<<< orphan*/  vlc_clock_slave_to_system_locked ; 
 int /*<<< orphan*/  vlc_clock_slave_update ; 

__attribute__((used)) static void vlc_clock_set_slave_callbacks(vlc_clock_t *clock)
{
    clock->update = vlc_clock_slave_update;
    clock->reset = vlc_clock_slave_reset;
    clock->set_delay = vlc_clock_slave_set_delay;
    clock->set_dejitter = vlc_clock_slave_set_dejitter;
    clock->to_system_locked = vlc_clock_slave_to_system_locked;
}