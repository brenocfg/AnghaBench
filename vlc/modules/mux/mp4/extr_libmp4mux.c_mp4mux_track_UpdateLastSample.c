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
struct TYPE_5__ {int i_samples_count; int /*<<< orphan*/  i_read_duration; TYPE_2__* samples; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;
struct TYPE_6__ {scalar_t__ i_length; } ;
typedef  TYPE_2__ mp4mux_sample_t ;

/* Variables and functions */

void mp4mux_track_UpdateLastSample(mp4mux_trackinfo_t *t,
                                   const mp4mux_sample_t *entry)
{
    if(t->i_samples_count)
    {
        mp4mux_sample_t *e = &t->samples[t->i_samples_count - 1];
        t->i_read_duration -= e->i_length;
        t->i_read_duration += entry->i_length;
        *e = *entry;
    }
}