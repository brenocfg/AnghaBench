#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {int /*<<< orphan*/  p_fifo; } ;
typedef  TYPE_1__ sout_input_t ;
struct TYPE_16__ {int /*<<< orphan*/  tinfo; scalar_t__ extrabuilder; } ;
typedef  TYPE_2__ mp4_stream_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_18__ {int i_codec; } ;

/* Variables and functions */
 TYPE_3__* AV1_Pack_Sample (TYPE_3__*) ; 
 TYPE_3__* ConvertSUBT (TYPE_3__*) ; 
#define  VLC_CODEC_AV1 131 
#define  VLC_CODEC_H264 130 
#define  VLC_CODEC_HEVC 129 
#define  VLC_CODEC_SUBT 128 
 TYPE_3__* block_FifoGet (int /*<<< orphan*/ ) ; 
 TYPE_3__* hxxx_AnnexB_to_xVC (TYPE_3__*,int) ; 
 TYPE_4__* mp4mux_track_GetFmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4mux_track_HasSamplePriv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4mux_track_SetSamplePriv (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  mux_extradata_builder_Feed (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t mux_extradata_builder_Get (scalar_t__,int /*<<< orphan*/  const**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static block_t * BlockDequeue(sout_input_t *p_input, mp4_stream_t *p_stream)
{
    block_t *p_block = block_FifoGet(p_input->p_fifo);
    if(unlikely(!p_block))
        return NULL;

    /* Create on the fly extradata as packetizer is not in the loop */
    if(p_stream->extrabuilder && !mp4mux_track_HasSamplePriv(p_stream->tinfo))
    {
         mux_extradata_builder_Feed(p_stream->extrabuilder,
                                    p_block->p_buffer, p_block->i_buffer);
         const uint8_t *p_extra;
         size_t i_extra = mux_extradata_builder_Get(p_stream->extrabuilder, &p_extra);
         if(i_extra)
            mp4mux_track_SetSamplePriv(p_stream->tinfo, p_extra, i_extra);
    }

    switch(mp4mux_track_GetFmt(p_stream->tinfo)->i_codec)
    {
        case VLC_CODEC_AV1:
            p_block = AV1_Pack_Sample(p_block);
            break;
        case VLC_CODEC_H264:
        case VLC_CODEC_HEVC:
            p_block = hxxx_AnnexB_to_xVC(p_block, 4);
            break;
        case VLC_CODEC_SUBT:
            p_block = ConvertSUBT(p_block);
            break;
        default:
            break;
    }

    return p_block;
}