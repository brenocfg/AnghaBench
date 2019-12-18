#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ i_samples_count; scalar_t__ i_samples_max; int b_hasbframes; int /*<<< orphan*/  i_read_duration; TYPE_2__* samples; } ;
typedef  TYPE_1__ mp4mux_trackinfo_t ;
struct TYPE_8__ {scalar_t__ i_pts_dts; int /*<<< orphan*/  i_length; } ;
typedef  TYPE_2__ mp4mux_sample_t ;

/* Variables and functions */
 scalar_t__ __MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlc_reallocarray (TYPE_2__*,scalar_t__,int) ; 

bool mp4mux_track_AddSample(mp4mux_trackinfo_t *t, const mp4mux_sample_t *entry)
{
    /* XXX: -1 to always have 2 entry for easy adding of empty SPU */
    if (t->i_samples_count + 2 >= t->i_samples_max)
    {
        if(t->i_samples_max + 1000 < t->i_samples_max)
            return false;
        mp4mux_sample_t *p_realloc = vlc_reallocarray(t->samples,
                                                      t->i_samples_max + 1000,
                                                      sizeof(*p_realloc));
        if(!p_realloc)
            return false;
        t->samples = p_realloc;
        t->i_samples_max += 1000;
    }
    t->samples[t->i_samples_count++] = *entry;
    if(!t->b_hasbframes && entry->i_pts_dts != 0)
        t->b_hasbframes = true;
    t->i_read_duration += __MAX(0, entry->i_length);
    return true;
}