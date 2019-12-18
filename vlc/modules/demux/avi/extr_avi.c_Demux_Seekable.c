#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int int64_t ;
struct TYPE_32__ {int /*<<< orphan*/  s; int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_33__ {unsigned int i_track; scalar_t__ i_time; scalar_t__ i_read_increment; scalar_t__ i_length; int i_movi_lastchunk_pos; int i_movi_begin; TYPE_7__** track; scalar_t__ b_seekable; scalar_t__ b_interleaved; scalar_t__ b_fastseekable; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_34__ {int /*<<< orphan*/  i_flags; scalar_t__ i_pts; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_35__ {int b_ok; int i_posf; int i_toread; } ;
typedef  TYPE_6__ avi_track_toread_t ;
struct TYPE_29__ {size_t i_size; TYPE_2__* p_entry; } ;
struct TYPE_30__ {scalar_t__ i_cat; int /*<<< orphan*/  i_codec; } ;
struct TYPE_36__ {int b_activated; int b_eof; size_t i_idxposc; scalar_t__ i_idxposb; int i_samplesize; int i_blockno; int i_blocksize; TYPE_11__ idx; TYPE_1__ fmt; scalar_t__ p_es_dv_audio; scalar_t__ p_es; } ;
typedef  TYPE_7__ avi_track_t ;
struct TYPE_37__ {unsigned int i_stream; scalar_t__ i_cat; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_peek; int /*<<< orphan*/  i_fourcc; } ;
typedef  TYPE_8__ avi_packet_t ;
struct TYPE_38__ {int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_lengthtotal; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_9__ avi_entry_t ;
struct TYPE_31__ {int i_pos; scalar_t__ i_length; int i_flags; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int AVIIF_KEYFRAME ; 
 scalar_t__ AVI_GetDPTS (TYPE_7__*,int) ; 
 int /*<<< orphan*/  AVI_GetKeyFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AVI_GetPTS (TYPE_7__*) ; 
 void* AVI_PTSToByte (TYPE_7__*,scalar_t__) ; 
 int AVI_PTSToChunk (TYPE_7__*,scalar_t__) ; 
 scalar_t__ AVI_PacketGetHeader (TYPE_3__*,TYPE_8__*) ; 
 scalar_t__ AVI_PacketNext (TYPE_3__*) ; 
 int /*<<< orphan*/  AVI_SendFrame (TYPE_3__*,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  AVI_TrackSeek (TYPE_3__*,unsigned int,scalar_t__) ; 
 scalar_t__ AVI_TrackStopFinishedStreams (TYPE_3__*) ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_I ; 
 int /*<<< orphan*/  BLOCK_FLAG_TYPE_PB ; 
 int /*<<< orphan*/  ES_OUT_GET_ES_STATE ; 
 TYPE_5__* ReadFrame (TYPE_3__*,TYPE_7__*,int,size_t) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int __MAX (int,int) ; 
 size_t __MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  avi_index_Append (TYPE_11__*,int*,TYPE_9__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Demux_Seekable( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    unsigned int i_track_count = 0;
    unsigned int i_track;
    /* cannot be more than 100 stream (dcXX or wbXX) */
    avi_track_toread_t toread[100];


    /* detect new selected/unselected streams */
    for( i_track = 0; i_track < p_sys->i_track; i_track++ )
    {
        avi_track_t *tk = p_sys->track[i_track];
        bool  b = false;

        es_out_Control( p_demux->out, ES_OUT_GET_ES_STATE, tk->p_es, &b );
        if( tk->p_es_dv_audio )
        {
            bool b_extra = false;
            es_out_Control( p_demux->out, ES_OUT_GET_ES_STATE, tk->p_es_dv_audio, &b_extra );
            b |= b_extra;
        }
        if( b && !tk->b_activated )
        {
            if( p_sys->b_seekable)
            {
                AVI_TrackSeek( p_demux, i_track, p_sys->i_time );
            }
            tk->b_activated = true;
        }
        else if( !b && tk->b_activated )
        {
            tk->b_activated = false;
        }
        if( b )
        {
            i_track_count++;
        }
    }

    if( i_track_count <= 0 )
    {
        p_sys->i_time += p_sys->i_read_increment;
        if( p_sys->i_length != 0 )
        {
            if( p_sys->i_time >= p_sys->i_length )
                return VLC_DEMUXER_EOF;
            return VLC_DEMUXER_SUCCESS;
        }
        msg_Warn( p_demux, "no track selected, exiting..." );
        return VLC_DEMUXER_EOF;
    }

    /* wait for the good time */
    es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_time );
    p_sys->i_time += p_sys->i_read_increment;

    /* init toread */
    for( i_track = 0; i_track < p_sys->i_track; i_track++ )
    {
        avi_track_t *tk = p_sys->track[i_track];

        toread[i_track].b_ok = tk->b_activated && !tk->b_eof;
        if( tk->i_idxposc < tk->idx.i_size )
        {
            toread[i_track].i_posf = tk->idx.p_entry[tk->i_idxposc].i_pos;
           if( tk->i_idxposb > 0 )
           {
                toread[i_track].i_posf += 8 + tk->i_idxposb;
           }
        }
        else
        {
            toread[i_track].i_posf = -1;
        }

        vlc_tick_t i_dpts = p_sys->i_time - AVI_GetPTS( tk );

        if( tk->i_samplesize )
        {
            toread[i_track].i_toread = AVI_PTSToByte( tk, i_dpts );
        }
        else if ( i_dpts > VLC_TICK_FROM_SEC(-2) ) /* don't send a too early dts (low fps video) */
        {
            int64_t i_chunks_count = AVI_PTSToChunk( tk, i_dpts );
            if( i_dpts > 0 && AVI_GetDPTS( tk, i_chunks_count ) < i_dpts )
            {
                /* AVI code is crap. toread is either bytes, or here, chunk count.
                 * That does not even work when reading amount < scale / rate */
                i_chunks_count++;
            }
            toread[i_track].i_toread = i_chunks_count;
        }
        else
            toread[i_track].i_toread = -1;
    }

    for( ;; )
    {
        avi_track_t     *tk;
        bool       b_done;
        block_t         *p_frame;
        int64_t i_pos;
        unsigned int i;
        size_t i_size;

        /* search for first chunk to be read */
        for( i = 0, b_done = true, i_pos = -1; i < p_sys->i_track; i++ )
        {
            if( !toread[i].b_ok ||
                ( p_sys->b_fastseekable && p_sys->b_interleaved &&
                  AVI_GetDPTS( p_sys->track[i], toread[i].i_toread ) <= -p_sys->i_read_increment ) )
            {
                continue;
            }

            if( toread[i].i_toread > 0 )
            {
                b_done = false; /* not yet finished */

                if( toread[i].i_posf > 0 )
                {
                    if( i_pos == -1 || i_pos > toread[i].i_posf )
                    {
                        i_track = i;
                        i_pos = toread[i].i_posf;
                    }
                }
            }
        }

        if( b_done )
        {
            for( i = 0; i < p_sys->i_track; i++ )
            {
                if( toread[i].b_ok && toread[i].i_toread >= 0 )
                    return VLC_DEMUXER_SUCCESS;
            }
            msg_Warn( p_demux, "all tracks have failed, exiting..." );
            return VLC_DEMUXER_EOF;
        }

        if( i_pos == -1 )
        {
            unsigned short i_loop_count = 0;

            /* no valid index, we will parse directly the stream
             * in case we fail we will disable all finished stream */
            if( p_sys->b_seekable && p_sys->i_movi_lastchunk_pos >= p_sys->i_movi_begin + 12 )
            {
                if (vlc_stream_Seek(p_demux->s, p_sys->i_movi_lastchunk_pos))
                    return VLC_DEMUXER_EGENERIC;

                if( AVI_PacketNext( p_demux ) )
                {
                    return( AVI_TrackStopFinishedStreams( p_demux ) ? 0 : 1 );
                }
            }
            else
            {
                if (vlc_stream_Seek(p_demux->s, p_sys->i_movi_begin + 12))
                    return VLC_DEMUXER_EGENERIC;
            }

            for( ;; )
            {
                avi_packet_t avi_pk;

                if( AVI_PacketGetHeader( p_demux, &avi_pk ) )
                {
                    msg_Warn( p_demux,
                             "cannot get packet header, track disabled" );
                    return( AVI_TrackStopFinishedStreams( p_demux ) ? 0 : 1 );
                }
                if( avi_pk.i_stream >= p_sys->i_track ||
                    ( avi_pk.i_cat != AUDIO_ES && avi_pk.i_cat != VIDEO_ES ) )
                {
                    if( AVI_PacketNext( p_demux ) )
                    {
                        msg_Warn( p_demux,
                                  "cannot skip packet, track disabled" );
                        return( AVI_TrackStopFinishedStreams( p_demux ) ? 0 : 1 );
                    }

                    if( !++i_loop_count )
                         msg_Warn( p_demux, "don't seem to find any data..." );
                    continue;
                }
                else
                {
                    i_track = avi_pk.i_stream;
                    tk = p_sys->track[i_track];

                    /* add this chunk to the index */
                    avi_entry_t index;
                    index.i_id     = avi_pk.i_fourcc;
                    index.i_flags  = AVI_GetKeyFlag(tk->fmt.i_codec, avi_pk.i_peek);
                    index.i_pos    = avi_pk.i_pos;
                    index.i_length = avi_pk.i_size;
                    index.i_lengthtotal = index.i_length;
                    avi_index_Append( &tk->idx, &p_sys->i_movi_lastchunk_pos, &index );

                    /* do we will read this data ? */
                    if( AVI_GetDPTS( tk, toread[i_track].i_toread ) > -p_sys->i_read_increment )
                    {
                        break;
                    }
                    else
                    {
                        if( AVI_PacketNext( p_demux ) )
                        {
                            msg_Warn( p_demux,
                                      "cannot skip packet, track disabled" );
                            return( AVI_TrackStopFinishedStreams( p_demux ) ? 0 : 1 );
                        }
                    }
                }
            }

        }
        else
        {
            if (vlc_stream_Seek(p_demux->s, i_pos))
                return VLC_DEMUXER_EGENERIC;
        }

        /* Set the track to use */
        tk = p_sys->track[i_track];

        /* read thoses data */
        if( tk->i_samplesize )
        {
            int64_t i_toread;

            if( ( i_toread = toread[i_track].i_toread ) <= 0 )
            {
                if( tk->i_samplesize > 1 )
                {
                    i_toread = tk->i_samplesize;
                }
                else
                {
                    i_toread = AVI_PTSToByte( tk, VLC_TICK_FROM_MS(20) );
                    i_toread = __MAX( i_toread, 100 );
                }
            }
            i_size = __MIN( tk->idx.p_entry[tk->i_idxposc].i_length -
                                tk->i_idxposb,
                            (size_t) i_toread );
        }
        else
        {
            i_size = tk->idx.p_entry[tk->i_idxposc].i_length;
        }

        if( tk->i_idxposb == 0 )
        {
            i_size += 8; /* need to read and skip header */
        }

        if( ( p_frame = ReadFrame( p_demux, tk,
                        ( tk->i_idxposb == 0 ) ? 8 : 0, i_size ) )==NULL )
        {
            msg_Warn( p_demux, "failed reading data" );
            tk->b_eof = false;
            toread[i_track].b_ok = false;
            continue;
        }

        p_frame->i_pts = VLC_TICK_0 + AVI_GetPTS( tk );
        if( tk->idx.p_entry[tk->i_idxposc].i_flags&AVIIF_KEYFRAME )
        {
            p_frame->i_flags = BLOCK_FLAG_TYPE_I;
        }
        else
        {
            p_frame->i_flags = BLOCK_FLAG_TYPE_PB;
        }

        /* read data */
        if( tk->i_samplesize )
        {
            if( tk->i_idxposb == 0 )
            {
                i_size -= 8;
            }
            toread[i_track].i_toread -= i_size;
            tk->i_idxposb += i_size;
            if( tk->i_idxposb >=
                    tk->idx.p_entry[tk->i_idxposc].i_length )
            {
                tk->i_idxposb = 0;
                tk->i_idxposc++;
            }
        }
        else
        {
            int i_length = tk->idx.p_entry[tk->i_idxposc].i_length;

            tk->i_idxposc++;
            if( tk->fmt.i_cat == AUDIO_ES )
            {
                tk->i_blockno += tk->i_blocksize > 0 ? ( i_length + tk->i_blocksize - 1 ) / tk->i_blocksize : 1;
            }
            toread[i_track].i_toread--;
        }

        if( tk->i_idxposc < tk->idx.i_size)
        {
            toread[i_track].i_posf =
                tk->idx.p_entry[tk->i_idxposc].i_pos;
            if( tk->i_idxposb > 0 )
            {
                toread[i_track].i_posf += 8 + tk->i_idxposb;
            }

        }
        else
        {
            toread[i_track].i_posf = -1;
        }

        AVI_SendFrame( p_demux, tk, p_frame );
    }
}