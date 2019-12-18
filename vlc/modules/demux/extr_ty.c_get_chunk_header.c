#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {scalar_t__ i_cur_chunk; scalar_t__ i_stuff_cnt; int eof; int i_num_recs; int i_seq_rec; int b_first_chunk; int* rec_hdrs; scalar_t__ i_cur_rec; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int CHUNK_SIZE ; 
 scalar_t__ TIVO_PES_FILEID ; 
 scalar_t__ U32_AT (int const*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,scalar_t__) ; 
 int* parse_chunk_headers (int*,int,int*) ; 
 scalar_t__ parse_master (TYPE_1__*) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int const**,int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ ,int*,int) ; 
 int* xmalloc (int) ; 

__attribute__((used)) static int get_chunk_header(demux_t *p_demux)
{
    int i_readSize, i_num_recs;
    uint8_t *p_hdr_buf;
    const uint8_t *p_peek;
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_payload_size;             /* sum of all records' sizes */

    msg_Dbg(p_demux, "parsing ty chunk #%d", p_sys->i_cur_chunk );

    /* if we have left-over filler space from the last chunk, get that */
    if (p_sys->i_stuff_cnt > 0) {
        if(vlc_stream_Read(p_demux->s, NULL, p_sys->i_stuff_cnt) != p_sys->i_stuff_cnt)
            return 0;
        p_sys->i_stuff_cnt = 0;
    }

    /* read the TY packet header */
    i_readSize = vlc_stream_Peek( p_demux->s, &p_peek, 4 );
    p_sys->i_cur_chunk++;

    if ( (i_readSize < 4) || ( U32_AT(&p_peek[ 0 ] ) == 0 ))
    {
        /* EOF */
        p_sys->eof = 1;
        return 0;
    }

    /* check if it's a PART Header */
    if( U32_AT( &p_peek[ 0 ] ) == TIVO_PES_FILEID )
    {
        /* parse master chunk */
        if(parse_master(p_demux) != VLC_SUCCESS)
            return 0;
        return get_chunk_header(p_demux);
    }

    /* number of records in chunk (8- or 16-bit number) */
    if (p_peek[3] & 0x80)
    {
        /* 16 bit rec cnt */
        p_sys->i_num_recs = i_num_recs = (p_peek[1] << 8) + p_peek[0];
        p_sys->i_seq_rec = (p_peek[3] << 8) + p_peek[2];
        if (p_sys->i_seq_rec != 0xffff)
        {
            p_sys->i_seq_rec &= ~0x8000;
        }
    }
    else
    {
        /* 8 bit reclen - tivo 1.3 format */
        p_sys->i_num_recs = i_num_recs = p_peek[0];
        p_sys->i_seq_rec = p_peek[1];
    }
    p_sys->i_cur_rec = 0;
    p_sys->b_first_chunk = false;

    /*msg_Dbg( p_demux, "chunk has %d records", i_num_recs );*/

    free(p_sys->rec_hdrs);
    p_sys->rec_hdrs = NULL;

    /* skip past the 4 bytes we "peeked" earlier */
    if(vlc_stream_Read(p_demux->s, NULL, 4) != 4)
        return 0;

    /* read the record headers into a temp buffer */
    p_hdr_buf = xmalloc(i_num_recs * 16);
    if (vlc_stream_Read(p_demux->s, p_hdr_buf, i_num_recs * 16) < i_num_recs * 16) {
        free( p_hdr_buf );
        p_sys->eof = true;
        return 0;
    }
    /* parse them */
    p_sys->rec_hdrs = parse_chunk_headers(p_hdr_buf, i_num_recs,
            &i_payload_size);
    free(p_hdr_buf);

    p_sys->i_stuff_cnt = CHUNK_SIZE - 4 -
        (p_sys->i_num_recs * 16) - i_payload_size;
    if (p_sys->i_stuff_cnt > 0)
        msg_Dbg( p_demux, "chunk has %d stuff bytes at end",
                 p_sys->i_stuff_cnt );
    return 1;
}