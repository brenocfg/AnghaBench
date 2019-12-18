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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_read_duration; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;

/* Variables and functions */

void mp4mux_track_ForceDuration(mp4mux_trackinfo_t *t, vlc_tick_t d)
{
    t->i_read_duration = d;
}