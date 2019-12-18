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
typedef  float vlc_tick_t ;
struct TYPE_3__ {float i_pts_delay; float rate; } ;
typedef  TYPE_1__ input_clock_t ;

/* Variables and functions */

__attribute__((used)) static vlc_tick_t ClockGetTsOffset( input_clock_t *cl )
{
    return cl->i_pts_delay * ( 1.0f / cl->rate - 1.0f );
}