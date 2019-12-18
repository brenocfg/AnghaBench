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

/* Variables and functions */
 int /*<<< orphan*/  g_debug (char*,double,double) ; 
 double g_timer_elapsed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timer_new () ; 
 int /*<<< orphan*/  global_timer ; 

void rofi_timings_init ( void )
{
    global_timer = g_timer_new ();
    double now = g_timer_elapsed ( global_timer, NULL );
    g_debug ( "%4.6f (%2.6f): Started", now, 0.0 );
}