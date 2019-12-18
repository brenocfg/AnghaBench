#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_15__ {scalar_t__ i_movi_lastchunk_pos; scalar_t__ i_movi_begin; size_t i_track; TYPE_4__** track; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_16__ {int /*<<< orphan*/  idx; TYPE_1__ fmt; } ;
typedef  TYPE_4__ avi_track_t ;
struct TYPE_17__ {size_t i_stream; scalar_t__ i_cat; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_peek; int /*<<< orphan*/  i_fourcc; } ;
typedef  TYPE_5__ avi_packet_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_lengthtotal; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_6__ avi_entry_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  AVI_GetKeyFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AVI_PacketGetHeader (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ AVI_PacketNext (TYPE_2__*) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  avi_index_Append (int /*<<< orphan*/ *,scalar_t__*,TYPE_6__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int AVI_StreamChunkFind( demux_t *p_demux, unsigned int i_stream )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    avi_packet_t avi_pk;
    unsigned short i_loop_count = 0;

    /* find first chunk of i_stream that isn't in index */

    if( p_sys->i_movi_lastchunk_pos >= p_sys->i_movi_begin + 12 )
    {
        if (vlc_stream_Seek(p_demux->s, p_sys->i_movi_lastchunk_pos))
            return VLC_EGENERIC;
        if( AVI_PacketNext( p_demux ) )
        {
            return VLC_EGENERIC;
        }
    }
    else
    {
        if (vlc_stream_Seek(p_demux->s, p_sys->i_movi_begin + 12))
            return VLC_EGENERIC;
    }

    for( ;; )
    {
        if( AVI_PacketGetHeader( p_demux, &avi_pk ) )
        {
            msg_Warn( p_demux, "cannot get packet header" );
            return VLC_EGENERIC;
        }
        if( avi_pk.i_stream >= p_sys->i_track ||
            ( avi_pk.i_cat != AUDIO_ES && avi_pk.i_cat != VIDEO_ES ) )
        {
            if( AVI_PacketNext( p_demux ) )
            {
                return VLC_EGENERIC;
            }

            if( !++i_loop_count )
                 msg_Warn( p_demux, "don't seem to find any data..." );
        }
        else
        {
            avi_track_t *tk_pk = p_sys->track[avi_pk.i_stream];

            /* add this chunk to the index */
            avi_entry_t index;
            index.i_id     = avi_pk.i_fourcc;
            index.i_flags  = AVI_GetKeyFlag(tk_pk->fmt.i_codec, avi_pk.i_peek);
            index.i_pos    = avi_pk.i_pos;
            index.i_length = avi_pk.i_size;
            index.i_lengthtotal = index.i_length;
            avi_index_Append( &tk_pk->idx, &p_sys->i_movi_lastchunk_pos, &index );

            if( avi_pk.i_stream == i_stream  )
            {
                return VLC_SUCCESS;
            }

            if( AVI_PacketNext( p_demux ) )
            {
                return VLC_EGENERIC;
            }
        }
    }
}