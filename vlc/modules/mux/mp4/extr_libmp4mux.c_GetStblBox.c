#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {scalar_t__ i_cat; } ;
struct TYPE_10__ {unsigned int i_samples_count; TYPE_3__* samples; TYPE_1__ fmt; int /*<<< orphan*/  i_timescale; scalar_t__ b_hasbframes; } ;
typedef  TYPE_2__ mp4mux_trackinfo_t ;
struct TYPE_11__ {int i_pos; int i_size; scalar_t__ i_pts_dts; scalar_t__ i_length; int i_flags; } ;
typedef  TYPE_3__ mp4mux_sample_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int BLOCK_FLAG_TYPE_I ; 
 int GetScaledEntryDuration (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/ * GetSounBox (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * GetTextBox (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * GetVideBox (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ SPU_ES ; 
 scalar_t__ VIDEO_ES ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_64be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bo_swap_32be (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/ * box_full_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int samples_from_vlc_tick (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bo_t *GetStblBox(vlc_object_t *p_obj, mp4mux_trackinfo_t *p_track, bool b_mov, bool b_stco64)
{
    /* sample description */
    bo_t *stsd = box_full_new("stsd", 0, 0);
    if(!stsd)
        return NULL;
    bo_add_32be(stsd, 1);
    if (p_track->fmt.i_cat == AUDIO_ES)
        box_gather(stsd, GetSounBox(p_obj, p_track, b_mov));
    else if (p_track->fmt.i_cat == VIDEO_ES)
        box_gather(stsd, GetVideBox(p_obj, p_track, b_mov));
    else if (p_track->fmt.i_cat == SPU_ES)
        box_gather(stsd, GetTextBox(p_obj, p_track, b_mov));

    /* chunk offset table */
    bo_t *stco;

    if (b_stco64) {
        /* 64 bits version */
        stco = box_full_new("co64", 0, 0);
    } else {
        /* 32 bits version */
        stco = box_full_new("stco", 0, 0);
    }
    if(!stco)
    {
        bo_free(stsd);
        return NULL;
    }
    bo_add_32be(stco, 0);     // entry-count (fixed latter)

    /* sample to chunk table */
    bo_t *stsc = box_full_new("stsc", 0, 0);
    if(!stsc)
    {
        bo_free(stco);
        bo_free(stsd);
        return NULL;
    }
    bo_add_32be(stsc, 0);     // entry-count (fixed latter)

    unsigned i_chunk = 0;
    unsigned i_stsc_last_val = 0, i_stsc_entries = 0;
    for (unsigned i = 0; i < p_track->i_samples_count; i_chunk++) {
        mp4mux_sample_t *entry = p_track->samples;
        int i_first = i;

        if (b_stco64)
            bo_add_64be(stco, entry[i].i_pos);
        else
            bo_add_32be(stco, entry[i].i_pos);

        for (; i < p_track->i_samples_count; i++)
            if (i >= p_track->i_samples_count - 1 ||
                    entry[i].i_pos + entry[i].i_size != entry[i+1].i_pos) {
                i++;
                break;
            }

        /* Add entry to the stsc table */
        if (i_stsc_last_val != i - i_first) {
            bo_add_32be(stsc, 1 + i_chunk);   // first-chunk
            bo_add_32be(stsc, i - i_first) ;  // samples-per-chunk
            bo_add_32be(stsc, 1);             // sample-descr-index
            i_stsc_last_val = i - i_first;
            i_stsc_entries++;
        }
    }

    /* Fix stco entry count */
    bo_swap_32be(stco, 12, i_chunk);
    if(p_obj)
        msg_Dbg(p_obj, "created %d chunks (stco)", i_chunk);

    /* Fix stsc entry count */
    bo_swap_32be(stsc, 12, i_stsc_entries );

    /* add stts */
    bo_t *stts = box_full_new("stts", 0, 0);
    if(!stts)
    {
        bo_free(stsd);
        bo_free(stco);
        bo_free(stsc);
        return NULL;
    }
    bo_add_32be(stts, 0);     // entry-count (fixed latter)

    vlc_tick_t i_total_mtime = 0;
    int64_t i_total_scaled = 0;
    unsigned i_index = 0;
    for (unsigned i = 0; i < p_track->i_samples_count; i_index++) {
        int     i_first = i;

        int64_t i_scaled = GetScaledEntryDuration(&p_track->samples[i], p_track->i_timescale,
                                                  &i_total_mtime, &i_total_scaled);
        for (unsigned j=i+1; j < p_track->i_samples_count; j++)
        {
            vlc_tick_t i_total_mtime_next = i_total_mtime;
            int64_t i_total_scaled_next = i_total_scaled;
            int64_t i_scalednext = GetScaledEntryDuration(&p_track->samples[j], p_track->i_timescale,
                                                          &i_total_mtime_next, &i_total_scaled_next);
            if( i_scalednext != i_scaled )
                break;

            i_total_mtime = i_total_mtime_next;
            i_total_scaled = i_total_scaled_next;
            i = j;
        }

        bo_add_32be(stts, ++i - i_first); // sample-count
        bo_add_32be(stts, i_scaled); // sample-delta
    }
    bo_swap_32be(stts, 12, i_index);

    //msg_Dbg(p_obj, "total sout duration %"PRId64" reconverted from scaled %"PRId64,
    //                i_total_mtime, vlc_tick_from_samples(i_total_scaled, p_track->i_timescale) );

    /* composition time handling */
    bo_t *ctts = NULL;
    if ( p_track->b_hasbframes && (ctts = box_full_new("ctts", 0, 0)) )
    {
        bo_add_32be(ctts, 0);
        i_index = 0;
        for (unsigned i = 0; i < p_track->i_samples_count; i_index++)
        {
            int     i_first = i;
            vlc_tick_t i_offset = p_track->samples[i].i_pts_dts;

            for (; i < p_track->i_samples_count; ++i)
                if (i == p_track->i_samples_count || p_track->samples[i].i_pts_dts != i_offset)
                    break;

            bo_add_32be(ctts, i - i_first); // sample-count
            bo_add_32be(ctts, samples_from_vlc_tick(i_offset, p_track->i_timescale) ); // sample-offset
        }
        bo_swap_32be(ctts, 12, i_index);
    }

    bo_t *stsz = box_full_new("stsz", 0, 0);
    if(!stsz)
    {
        bo_free(stsd);
        bo_free(stco);
        bo_free(stts);
        return NULL;
    }
    int i_size = 0;
    for (unsigned i = 0; i < p_track->i_samples_count; i++)
    {
        if ( i == 0 )
            i_size = p_track->samples[i].i_size;
        else if ( p_track->samples[i].i_size != i_size )
        {
            i_size = 0;
            break;
        }
    }
    bo_add_32be(stsz, i_size);                         // sample-size
    bo_add_32be(stsz, p_track->i_samples_count);       // sample-count
    if ( i_size == 0 ) // all samples have different size
    {
        for (unsigned i = 0; i < p_track->i_samples_count; i++)
            bo_add_32be(stsz, p_track->samples[i].i_size); // sample-size
    }

    /* create stss table */
    bo_t *stss = NULL;
    i_index = 0;
    if ( p_track->fmt.i_cat == VIDEO_ES || p_track->fmt.i_cat == AUDIO_ES )
    {
        vlc_tick_t i_interval = -1;
        for (unsigned i = 0; i < p_track->i_samples_count; i++)
        {
            if ( i_interval != -1 )
            {
                i_interval += p_track->samples[i].i_length + p_track->samples[i].i_pts_dts;
                if ( i_interval < VLC_TICK_FROM_SEC(2) )
                    continue;
            }

            if (p_track->samples[i].i_flags & BLOCK_FLAG_TYPE_I) {
                if (stss == NULL) {
                    stss = box_full_new("stss", 0, 0);
                    if(!stss)
                        break;
                    bo_add_32be(stss, 0); /* fixed later */
                }
                bo_add_32be(stss, 1 + i);
                i_index++;
                i_interval = 0;
            }
        }
    }

    if (stss)
        bo_swap_32be(stss, 12, i_index);

    /* Now gather all boxes into stbl */
    bo_t *stbl = box_new("stbl");
    if(!stbl)
    {
        bo_free(stsd);
        bo_free(stco);
        bo_free(stts);
        bo_free(stsz);
        bo_free(stss);
        bo_free(ctts);
        return NULL;
    }
    box_gather(stbl, stsd);
    box_gather(stbl, stts);
    if (stss)
        box_gather(stbl, stss);
    if (ctts)
        box_gather(stbl, ctts);
    box_gather(stbl, stsc);
    box_gather(stbl, stsz);
    box_gather(stbl, stco);

    return stbl;
}