#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t stime_t ;
struct TYPE_19__ {int i_flags; size_t i_sample_count; TYPE_2__* p_samples; } ;
struct TYPE_16__ {TYPE_4__* p_trun; } ;
struct TYPE_18__ {scalar_t__ i_type; struct TYPE_18__ const* p_next; TYPE_1__ data; } ;
struct TYPE_17__ {scalar_t__ i_duration; } ;
struct TYPE_15__ {unsigned int i_track_ID; size_t i_default_sample_duration; size_t i_timescale; int i_flags; } ;
typedef  TYPE_3__ const MP4_Box_t ;
typedef  TYPE_4__ MP4_Box_data_trun_t ;

/* Variables and functions */
 scalar_t__ ATOM_traf ; 
 scalar_t__ ATOM_trun ; 
 TYPE_13__* BOXDATA (TYPE_3__ const*) ; 
 TYPE_3__ const* MP4_BoxGet (TYPE_3__ const*,char*) ; 
 TYPE_3__ const* MP4_GetTrakByTrackID (TYPE_3__ const*,unsigned int) ; 
 TYPE_3__ const* MP4_GetTrexByTrackID (TYPE_3__ const*,unsigned int) ; 
 int MP4_TFHD_DFLT_SAMPLE_DURATION ; 
 int MP4_TRUN_SAMPLE_DURATION ; 

__attribute__((used)) static bool GetMoofTrackDuration( MP4_Box_t *p_moov, MP4_Box_t *p_moof,
                                  unsigned i_track_ID, stime_t *p_duration )
{
    if ( !p_moof || !p_moov )
        return false;

    MP4_Box_t *p_traf = MP4_BoxGet( p_moof, "traf" );
    while ( p_traf )
    {
        if ( p_traf->i_type != ATOM_traf )
        {
           p_traf = p_traf->p_next;
           continue;
        }

        const MP4_Box_t *p_tfhd = MP4_BoxGet( p_traf, "tfhd" );
        const MP4_Box_t *p_trun = MP4_BoxGet( p_traf, "trun" );
        if ( !p_tfhd || !p_trun || i_track_ID != BOXDATA(p_tfhd)->i_track_ID )
        {
           p_traf = p_traf->p_next;
           continue;
        }

        uint32_t i_track_timescale = 0;
        uint32_t i_track_defaultsampleduration = 0;

        /* set trex for defaults */
        MP4_Box_t *p_trex = MP4_GetTrexByTrackID( p_moov, BOXDATA(p_tfhd)->i_track_ID );
        if ( p_trex )
        {
            i_track_defaultsampleduration = BOXDATA(p_trex)->i_default_sample_duration;
        }

        MP4_Box_t *p_trak = MP4_GetTrakByTrackID( p_moov, BOXDATA(p_tfhd)->i_track_ID );
        if ( p_trak )
        {
            MP4_Box_t *p_mdhd = MP4_BoxGet( p_trak, "mdia/mdhd" );
            if ( p_mdhd )
                i_track_timescale = BOXDATA(p_mdhd)->i_timescale;
        }

        if ( !i_track_timescale )
        {
           p_traf = p_traf->p_next;
           continue;
        }

        uint64_t i_traf_duration = 0;
        while ( p_trun && p_tfhd )
        {
            if ( p_trun->i_type != ATOM_trun )
            {
               p_trun = p_trun->p_next;
               continue;
            }
            const MP4_Box_data_trun_t *p_trundata = p_trun->data.p_trun;

            /* Sum total time */
            if ( p_trundata->i_flags & MP4_TRUN_SAMPLE_DURATION )
            {
                for( uint32_t i=0; i< p_trundata->i_sample_count; i++ )
                    i_traf_duration += p_trundata->p_samples[i].i_duration;
            }
            else if ( BOXDATA(p_tfhd)->i_flags & MP4_TFHD_DFLT_SAMPLE_DURATION )
            {
                i_traf_duration += p_trundata->i_sample_count *
                        BOXDATA(p_tfhd)->i_default_sample_duration;
            }
            else
            {
                i_traf_duration += p_trundata->i_sample_count *
                        i_track_defaultsampleduration;
            }

            p_trun = p_trun->p_next;
        }

        *p_duration = i_traf_duration;
        break;
    }

    return true;
}