#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int i_chunk_count; scalar_t__ i_sample_count; int /*<<< orphan*/  i_track_ID; TYPE_2__* chunk; int /*<<< orphan*/  p_stbl; } ;
typedef  TYPE_1__ mp4_track_t ;
struct TYPE_7__ {scalar_t__ i_sample_count; scalar_t__ i_sample_first; int /*<<< orphan*/  i_sample_description_index; int /*<<< orphan*/ * p_sample_offset_pts; int /*<<< orphan*/ * p_sample_count_pts; scalar_t__ i_entries_pts; int /*<<< orphan*/ * p_sample_delta_dts; int /*<<< orphan*/ * p_sample_count_dts; scalar_t__ i_entries_dts; scalar_t__ i_first_dts; int /*<<< orphan*/  i_offset; } ;
typedef  TYPE_2__ mp4_chunk_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_8__ {unsigned int i_entry_count; int* i_first_chunk; scalar_t__* i_samples_per_chunk; int /*<<< orphan*/ * i_sample_description_index; int /*<<< orphan*/ * i_chunk_offset; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_5__* BOXDATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MP4_BoxGet (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ UINT32_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_2__* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int TrackCreateChunksIndex( demux_t *p_demux,
                                   mp4_track_t *p_demux_track )
{
    MP4_Box_t *p_co64; /* give offset for each chunk, same for stco and co64 */
    MP4_Box_t *p_stsc;

    unsigned int i_chunk;
    unsigned int i_index, i_last;

    if( ( !(p_co64 = MP4_BoxGet( p_demux_track->p_stbl, "stco" ) )&&
          !(p_co64 = MP4_BoxGet( p_demux_track->p_stbl, "co64" ) ) )||
        ( !(p_stsc = MP4_BoxGet( p_demux_track->p_stbl, "stsc" ) ) ))
    {
        return( VLC_EGENERIC );
    }

    p_demux_track->i_chunk_count = BOXDATA(p_co64)->i_entry_count;
    if( !p_demux_track->i_chunk_count )
    {
        msg_Warn( p_demux, "no chunk defined" );
    }
    p_demux_track->chunk = calloc( p_demux_track->i_chunk_count,
                                   sizeof( mp4_chunk_t ) );
    if( p_demux_track->chunk == NULL )
    {
        return VLC_ENOMEM;
    }

    /* first we read chunk offset */
    for( i_chunk = 0; i_chunk < p_demux_track->i_chunk_count; i_chunk++ )
    {
        mp4_chunk_t *ck = &p_demux_track->chunk[i_chunk];

        ck->i_offset = BOXDATA(p_co64)->i_chunk_offset[i_chunk];

        ck->i_first_dts = 0;
        ck->i_entries_dts = 0;
        ck->p_sample_count_dts = NULL;
        ck->p_sample_delta_dts = NULL;
        ck->i_entries_pts = 0;
        ck->p_sample_count_pts = NULL;
        ck->p_sample_offset_pts = NULL;
    }

    /* now we read index for SampleEntry( soun vide mp4a mp4v ...)
        to be used for the sample XXX begin to 1
        We construct it begining at the end */
    i_last = p_demux_track->i_chunk_count; /* last chunk proceded */
    i_index = BOXDATA(p_stsc)->i_entry_count;

    while( i_index-- > 0 )
    {
        for( i_chunk = BOXDATA(p_stsc)->i_first_chunk[i_index] - 1;
             i_chunk < i_last; i_chunk++ )
        {
            if( i_chunk >= p_demux_track->i_chunk_count )
            {
                msg_Warn( p_demux, "corrupted chunk table" );
                return VLC_EGENERIC;
            }

            p_demux_track->chunk[i_chunk].i_sample_description_index =
                    BOXDATA(p_stsc)->i_sample_description_index[i_index];
            p_demux_track->chunk[i_chunk].i_sample_count =
                    BOXDATA(p_stsc)->i_samples_per_chunk[i_index];
        }
        i_last = BOXDATA(p_stsc)->i_first_chunk[i_index] - 1;
    }

    p_demux_track->i_sample_count = 0;
    bool b_broken = false;
    if ( p_demux_track->i_chunk_count )
    {
        p_demux_track->chunk[0].i_sample_first = 0;
        p_demux_track->i_sample_count += p_demux_track->chunk[0].i_sample_count;

        const mp4_chunk_t *prev = &p_demux_track->chunk[0];
        for( i_chunk = 1; i_chunk < p_demux_track->i_chunk_count; i_chunk++ )
        {
            mp4_chunk_t *cur = &p_demux_track->chunk[i_chunk];
            if( unlikely(UINT32_MAX - cur->i_sample_count < p_demux_track->i_sample_count) )
            {
                b_broken = true;
                break;
            }
            p_demux_track->i_sample_count += cur->i_sample_count;
            cur->i_sample_first = prev->i_sample_first + prev->i_sample_count;
            prev = cur;
        }
    }

    if( unlikely(b_broken) )
    {
        msg_Err( p_demux, "Overflow in chunks total samples count" );
        return VLC_EGENERIC;
    }

    msg_Dbg( p_demux, "track[Id 0x%x] read %d chunk",
             p_demux_track->i_track_ID, p_demux_track->i_chunk_count );

    return VLC_SUCCESS;
}