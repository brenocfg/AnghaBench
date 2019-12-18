#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_8__ {int subrec_type; int rec_type; int l_rec_size; } ;
typedef  TYPE_1__ ty_rec_hdr_t ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_10__ {scalar_t__ tivo_series; scalar_t__ tivo_type; int /*<<< orphan*/  i_Pts_Offset; int /*<<< orphan*/  audio_type; int /*<<< orphan*/  i_Pes_Length; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC3_PES_LENGTH ; 
 int /*<<< orphan*/  AC3_PTS_OFFSET ; 
 int /*<<< orphan*/  DTIVO_PTS_OFFSET ; 
 int /*<<< orphan*/  SA_PTS_OFFSET ; 
 int /*<<< orphan*/  SERIES1_PES_LENGTH ; 
 int /*<<< orphan*/  SERIES2_PES_LENGTH ; 
 int /*<<< orphan*/  TIVO_AUDIO_AC3 ; 
 int /*<<< orphan*/  TIVO_AUDIO_MPEG ; 
 scalar_t__ TIVO_PES_FILEID ; 
 scalar_t__ TIVO_SERIES1 ; 
 scalar_t__ TIVO_SERIES2 ; 
 void* TIVO_TYPE_DTIVO ; 
 scalar_t__ TIVO_TYPE_SA ; 
 scalar_t__ TIVO_TYPE_UNKNOWN ; 
 scalar_t__ U32_AT (int const*) ; 
 int find_es_header (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,...) ; 
 TYPE_1__* parse_chunk_headers (int const*,int,int*) ; 
 int /*<<< orphan*/  ty_MPEGAudioPacket ; 

__attribute__((used)) static void analyze_chunk(demux_t *p_demux, const uint8_t *p_chunk)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_num_recs, i;
    ty_rec_hdr_t *p_hdrs;
    int i_num_6e0, i_num_be0, i_num_9c0, i_num_3c0;
    int i_payload_size;

    /* skip if it's a Part header */
    if( U32_AT( &p_chunk[ 0 ] ) == TIVO_PES_FILEID )
        return;

    /* number of records in chunk (we ignore high order byte;
     * rarely are there > 256 chunks & we don't need that many anyway) */
    i_num_recs = p_chunk[0];
    if (i_num_recs < 5) {
        /* try again with the next chunk.  Sometimes there are dead ones */
        return;
    }

    p_chunk += 4;       /* skip past rec count & SEQ bytes */
    //msg_Dbg(p_demux, "probe: chunk has %d recs", i_num_recs);
    p_hdrs = parse_chunk_headers(p_chunk, i_num_recs, &i_payload_size);
    /* scan headers.
     * 1. check video packets.  Presence of 0x6e0 means S1.
     *    No 6e0 but have be0 means S2.
     * 2. probe for audio 0x9c0 vs 0x3c0 (AC3 vs Mpeg)
     *    If AC-3, then we have DTivo.
     *    If MPEG, search for PTS offset.  This will determine SA vs. DTivo.
     */
    i_num_6e0 = i_num_be0 = i_num_9c0 = i_num_3c0 = 0;
    for (i=0; i<i_num_recs; i++) {
        //msg_Dbg(p_demux, "probe: rec is %d/%d = 0x%04x", p_hdrs[i].subrec_type,
            //p_hdrs[i].rec_type,
            //p_hdrs[i].subrec_type << 8 | p_hdrs[i].rec_type);
        switch (p_hdrs[i].subrec_type << 8 | p_hdrs[i].rec_type) {
            case 0x6e0:
                i_num_6e0++;
                break;
            case 0xbe0:
                i_num_be0++;
                break;
            case 0x3c0:
                i_num_3c0++;
                break;
            case 0x9c0:
                i_num_9c0++;
                break;
        }
    }
    msg_Dbg(p_demux, "probe: chunk has %d 0x6e0 recs, %d 0xbe0 recs.",
        i_num_6e0, i_num_be0);

    /* set up our variables */
    if (i_num_6e0 > 0) {
        msg_Dbg(p_demux, "detected Series 1 Tivo");
        p_sys->tivo_series = TIVO_SERIES1;
        p_sys->i_Pes_Length = SERIES1_PES_LENGTH;
    } else if (i_num_be0 > 0) {
        msg_Dbg(p_demux, "detected Series 2 Tivo");
        p_sys->tivo_series = TIVO_SERIES2;
        p_sys->i_Pes_Length = SERIES2_PES_LENGTH;
    }
    if (i_num_9c0 > 0) {
        msg_Dbg(p_demux, "detected AC-3 Audio (DTivo)" );
        p_sys->audio_type = TIVO_AUDIO_AC3;
        p_sys->tivo_type = TIVO_TYPE_DTIVO;
        p_sys->i_Pts_Offset = AC3_PTS_OFFSET;
        p_sys->i_Pes_Length = AC3_PES_LENGTH;
    } else if (i_num_3c0 > 0) {
        p_sys->audio_type = TIVO_AUDIO_MPEG;
        msg_Dbg(p_demux, "detected MPEG Audio" );
    }

    /* if tivo_type still unknown, we can check PTS location
     * in MPEG packets to determine tivo_type */
    if (p_sys->tivo_type == TIVO_TYPE_UNKNOWN) {
        uint32_t i_data_offset = (16 * i_num_recs);
        for (i=0; i<i_num_recs; i++) {
            if ((p_hdrs[i].subrec_type << 0x08 | p_hdrs[i].rec_type) == 0x3c0 &&
                    p_hdrs[i].l_rec_size > 15) {
                /* first make sure we're aligned */
                int i_pes_offset = find_es_header(ty_MPEGAudioPacket,
                        &p_chunk[i_data_offset], 5);
                if (i_pes_offset >= 0) {
                    /* pes found. on SA, PES has hdr data at offset 6, not PTS. */
                    //msg_Dbg(p_demux, "probe: mpeg es header found in rec %d at offset %d",
                            //i, i_pes_offset);
                    if ((p_chunk[i_data_offset + 6 + i_pes_offset] & 0x80) == 0x80) {
                        /* S1SA or S2(any) Mpeg Audio (PES hdr, not a PTS start) */
                        if (p_sys->tivo_series == TIVO_SERIES1)
                            msg_Dbg(p_demux, "detected Stand-Alone Tivo" );
                        p_sys->tivo_type = TIVO_TYPE_SA;
                        p_sys->i_Pts_Offset = SA_PTS_OFFSET;
                    } else {
                        if (p_sys->tivo_series == TIVO_SERIES1)
                            msg_Dbg(p_demux, "detected DirecTV Tivo" );
                        p_sys->tivo_type = TIVO_TYPE_DTIVO;
                        p_sys->i_Pts_Offset = DTIVO_PTS_OFFSET;
                    }
                    break;
                }
            }
            i_data_offset += p_hdrs[i].l_rec_size;
        }
    }
    free(p_hdrs);
}