#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ i_cat; int i_codec; scalar_t__ i_original_fourcc; } ;
struct TYPE_14__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ mp4_track_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ ATOM_rrtp ; 
 TYPE_3__* AV1_Unpack_Sample (TYPE_3__*) ; 
 TYPE_3__* MP4_EIA608_Convert (TYPE_3__*) ; 
 TYPE_3__* MP4_RTPHint_Convert (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ SPU_ES ; 
 int VLC_CODEC_AV1 ; 
#define  VLC_CODEC_CEA608 135 
#define  VLC_CODEC_CEA708 134 
#define  VLC_CODEC_QTXT 133 
#define  VLC_CODEC_SPU 132 
#define  VLC_CODEC_SUBT 131 
#define  VLC_CODEC_TTML 130 
#define  VLC_CODEC_TX3G 129 
#define  VLC_CODEC_WEBVTT 128 

__attribute__((used)) static block_t * MP4_Block_Convert( demux_t *p_demux, const mp4_track_t *p_track, block_t *p_block )
{
    /* might have some encap */
    if( p_track->fmt.i_cat == SPU_ES )
    {
        switch( p_track->fmt.i_codec )
        {
            case VLC_CODEC_WEBVTT:
            case VLC_CODEC_TTML:
            case VLC_CODEC_QTXT:
            case VLC_CODEC_TX3G:
            case VLC_CODEC_SPU:
            case VLC_CODEC_SUBT:
            /* accept as-is */
            break;
            case VLC_CODEC_CEA608:
            case VLC_CODEC_CEA708:
                p_block = MP4_EIA608_Convert( p_block );
            break;
        default:
            p_block->i_buffer = 0;
            break;
        }
    }
    else if( p_track->fmt.i_codec == VLC_CODEC_AV1 )
    {
        p_block = AV1_Unpack_Sample( p_block );
    }
    else if( p_track->fmt.i_original_fourcc == ATOM_rrtp )
    {
        p_block = MP4_RTPHint_Convert( p_demux, p_block, p_track->fmt.i_codec );
    }

    return p_block;
}