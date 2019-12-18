#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int i_samples_count; TYPE_2__* samples; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_pos; } ;
typedef  TYPE_2__ mp4mux_sample_t ;
struct TYPE_8__ {int /*<<< orphan*/  tracks; } ;
typedef  TYPE_3__ mp4mux_handle_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 

void mp4mux_ShiftSamples(mp4mux_handle_t *h, int64_t offset)
{
    for(size_t i_track = 0; i_track < vlc_array_count(&h->tracks); i_track++)
    {
        mp4mux_trackinfo_t *t = vlc_array_item_at_index(&h->tracks, i_track);
        for (unsigned i = 0; i < t->i_samples_count; i++)
        {
            mp4mux_sample_t *sample = t->samples;
            sample[i].i_pos += offset;
        }
    }
}