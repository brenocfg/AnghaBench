#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  seq_end_pes ;
struct TYPE_10__ {int b_flushed; int /*<<< orphan*/  p_parser; int /*<<< orphan*/  pl_info_lock; TYPE_2__* p_clip_info; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;
typedef  int bd_stream_type_e ;
struct TYPE_9__ {TYPE_1__* video_streams; } ;
struct TYPE_8__ {int coding_type; } ;

/* Variables and functions */
#define  BD_STREAM_TYPE_VIDEO_HEVC 132 
#define  BLURAY_STREAM_TYPE_VIDEO_H264 131 
#define  BLURAY_STREAM_TYPE_VIDEO_MPEG1 130 
#define  BLURAY_STREAM_TYPE_VIDEO_MPEG2 129 
#define  BLURAY_STREAM_TYPE_VIDEO_VC1 128 
 TYPE_4__* block_Alloc (int) ; 
 int /*<<< orphan*/  vlc_demux_chained_Send (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeTsPacketWDiscontinuity (int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static void streamFlush( demux_sys_t *p_sys )
{
    /*
     * MPEG-TS demuxer does not flush last video frame if size of PES packet is unknown.
     * Packet is flushed only when TS packet with PUSI flag set is received.
     *
     * Fix this by emitting (video) ts packet with PUSI flag set.
     * Add video sequence end code to payload so that also video decoder is flushed.
     * Set PES packet size in the payload so that it will be sent to decoder immediately.
     */

    if (p_sys->b_flushed)
        return;

    block_t *p_block = block_Alloc(192);
    if (!p_block)
        return;

    bd_stream_type_e i_coding_type;

    /* set correct sequence end code */
    vlc_mutex_lock(&p_sys->pl_info_lock);
    if (p_sys->p_clip_info != NULL)
        i_coding_type = p_sys->p_clip_info->video_streams[0].coding_type;
    else
        i_coding_type = 0;
    vlc_mutex_unlock(&p_sys->pl_info_lock);

    uint8_t i_eos;
    switch( i_coding_type )
    {
        case BLURAY_STREAM_TYPE_VIDEO_MPEG1:
        case BLURAY_STREAM_TYPE_VIDEO_MPEG2:
        default:
            i_eos = 0xB7; /* MPEG2 sequence end */
            break;
        case BLURAY_STREAM_TYPE_VIDEO_VC1:
        case BLURAY_STREAM_TYPE_VIDEO_H264:
            i_eos = 0x0A; /* VC1 / H.264 sequence end */
            break;
        case BD_STREAM_TYPE_VIDEO_HEVC:
            i_eos = 0x48; /* HEVC sequence end NALU */
            break;
    }

    uint8_t seq_end_pes[] = {
        0x00, 0x00, 0x01, 0xe0, 0x00, 0x07, 0x80, 0x00, 0x00,  /* PES header */
        0x00, 0x00, 0x01, i_eos,                               /* PES payload: sequence end */
        0x00, /* 2nd byte for HEVC NAL, pads others */
    };

    writeTsPacketWDiscontinuity( p_block->p_buffer, 0x1011, seq_end_pes, sizeof(seq_end_pes) );

    vlc_demux_chained_Send(p_sys->p_parser, p_block);
    p_sys->b_flushed = true;
}