#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {long l_rec_size; int rec_type; int /*<<< orphan*/  b_ext; } ;
typedef  TYPE_1__ ty_rec_hdr_t ;
struct TYPE_20__ {int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_21__ {size_t i_cur_rec; size_t i_num_recs; TYPE_1__* rec_hdrs; scalar_t__ b_first_chunk; scalar_t__ eof; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DemuxRecAudio (TYPE_2__*,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  DemuxRecCc (TYPE_2__*,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  DemuxRecVideo (TYPE_2__*,TYPE_1__*,TYPE_4__*) ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 scalar_t__ get_chunk_header (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int) ; 
 TYPE_4__* vlc_stream_Block (int /*<<< orphan*/ ,long const) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t  *p_sys = p_demux->p_sys;
    ty_rec_hdr_t *p_rec;
    block_t      *p_block_in = NULL;

    /*msg_Dbg(p_demux, "ty demux processing" );*/

    /* did we hit EOF earlier? */
    if( p_sys->eof )
        return VLC_DEMUXER_EOF;

    /*
     * what we do (1 record now.. maybe more later):
    * - use vlc_stream_Read() to read the chunk header & record headers
    * - discard entire chunk if it is a PART header chunk
    * - parse all the headers into record header array
    * - keep a pointer of which record we're on
    * - use vlc_stream_Block() to fetch each record
    * - parse out PTS from PES headers
    * - set PTS for data packets
    * - pass the data on to the proper codec via es_out_Send()

    * if this is the first time or
    * if we're at the end of this chunk, start a new one
    */
    /* parse the next chunk's record headers */
    if( p_sys->b_first_chunk || p_sys->i_cur_rec >= p_sys->i_num_recs )
    {
        if( get_chunk_header(p_demux) == 0 || p_sys->i_num_recs == 0 )
            return VLC_DEMUXER_EOF;
    }

    /*======================================================================
     * parse & send one record of the chunk
     *====================================================================== */
    p_rec = &p_sys->rec_hdrs[p_sys->i_cur_rec];

    if( !p_rec->b_ext )
    {
        const long l_rec_size = p_rec->l_rec_size;
        /*msg_Dbg(p_demux, "Record Type 0x%x/%02x %ld bytes",
                    subrec_type, p_rec->rec_type, l_rec_size );*/

        /* some normal records are 0 length, so check for that... */
        if( l_rec_size <= 0 )
        {
            /* no data in payload; we're done */
            p_sys->i_cur_rec++;
            return VLC_DEMUXER_SUCCESS;
        }

        /* read in this record's payload */
        if( !( p_block_in = vlc_stream_Block( p_demux->s, l_rec_size ) ) )
            return VLC_DEMUXER_EOF;

        /* set these as 'unknown' for now */
        p_block_in->i_pts =
        p_block_in->i_dts = VLC_TICK_INVALID;
    }
    /*else
    {
        -- don't read any data from the stream, data was in the record header --
        msg_Dbg(p_demux,
               "Record Type 0x%02x/%02x, ext data = %02x, %02x", subrec_type,
                p_rec->rec_type, p_rec->ex1, p_rec->ex2);
    }*/

    switch( p_rec->rec_type )
    {
        case 0xe0: /* video */
            DemuxRecVideo( p_demux, p_rec, p_block_in );
            break;

        case 0xc0: /* audio */
            DemuxRecAudio( p_demux, p_rec, p_block_in );
            break;

        case 0x01:
        case 0x02:
            /* closed captions/XDS */
            DemuxRecCc( p_demux, p_rec, p_block_in );
            break;

        default:
            msg_Dbg(p_demux, "Invalid record type 0x%02x", p_rec->rec_type );
            /* fall-through */

        case 0x03: /* tivo data services */
        case 0x05: /* unknown, but seen regularly */
            if( p_block_in )
                block_Release( p_block_in );
    }

    /* */
    p_sys->i_cur_rec++;
    return VLC_DEMUXER_SUCCESS;
}