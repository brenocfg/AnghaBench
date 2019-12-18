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
struct TYPE_3__ {int i_samples_count; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;

/* Variables and functions */

unsigned mp4mux_track_GetSampleCount(const mp4mux_trackinfo_t *t)
{
    return t->i_samples_count;
}