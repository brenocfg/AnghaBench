#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ i_edits_count; scalar_t__ i_timescale; TYPE_1__* p_edits; } ;
typedef  TYPE_2__ mp4mux_trackinfo_t ;
typedef  int /*<<< orphan*/  bo_t ;
struct TYPE_4__ {scalar_t__ i_start_offset; scalar_t__ i_duration; scalar_t__ i_start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddEdit (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_full_new (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int samples_from_vlc_tick (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bo_t *GetEDTS( mp4mux_trackinfo_t *p_track, uint32_t i_movietimescale, bool b_64_ext)
{
    if(p_track->i_edits_count == 0)
        return NULL;

    bo_t *edts = box_new("edts");
    bo_t *elst = box_full_new("elst", b_64_ext ? 1 : 0, 0);
    if(!elst || !edts)
    {
        bo_free(elst);
        bo_free(edts);
        return NULL;
    }

    uint32_t i_total_edits = p_track->i_edits_count;
    for(unsigned i=0; i<p_track->i_edits_count; i++)
    {
        /* !WARN! media time must start sample time 0, we need a -1 edit for start offsets */
        if(p_track->p_edits[i].i_start_offset != 0)
            i_total_edits++;
    }

    bo_add_32be(elst, i_total_edits);

    for(unsigned i=0; i<p_track->i_edits_count; i++)
    {
        if(p_track->p_edits[i].i_start_offset != 0)
        {
            AddEdit(elst,
                    samples_from_vlc_tick(p_track->p_edits[i].i_start_offset, i_movietimescale),
                    -1,
                    b_64_ext);
        }

        /* !WARN AGAIN! Uses different Timescales ! */
        AddEdit(elst,
                samples_from_vlc_tick(p_track->p_edits[i].i_duration, i_movietimescale),
                samples_from_vlc_tick(p_track->p_edits[i].i_start_time, p_track->i_timescale),
                b_64_ext);
    }

    box_gather(edts, elst);
    return edts;
}