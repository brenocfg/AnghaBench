#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vlc_fourcc_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int AVIIF_KEYFRAME ; 
 int GetDWBE (int*) ; 
#define  VLC_CODEC_DIV1 132 
#define  VLC_CODEC_DIV2 131 
#define  VLC_CODEC_DIV3 130 
#define  VLC_CODEC_MP4V 129 
#define  VLC_CODEC_WMV1 128 

__attribute__((used)) static int AVI_GetKeyFlag( vlc_fourcc_t i_fourcc, uint8_t *p_byte )
{
    switch( i_fourcc )
    {
        case VLC_CODEC_DIV1:
            /* we have:
             *  startcode:      0x00000100   32bits
             *  framenumber     ?             5bits
             *  piture type     0(I),1(P)     2bits
             */
            if( GetDWBE( p_byte ) != 0x00000100 )
            {
                /* it's not an msmpegv1 stream, strange...*/
                return AVIIF_KEYFRAME;
            }
            return p_byte[4] & 0x06 ? 0 : AVIIF_KEYFRAME;

        case VLC_CODEC_DIV2:
        case VLC_CODEC_DIV3:
        case VLC_CODEC_WMV1:
            /* we have
             *  picture type    0(I),1(P)     2bits
             */
            return p_byte[0] & 0xC0 ? 0 : AVIIF_KEYFRAME;
        case VLC_CODEC_MP4V:
            /* we should find first occurrence of 0x000001b6 (32bits)
             *  startcode:      0x000001b6   32bits
             *  piture type     0(I),1(P)     2bits
             */
            if( GetDWBE( p_byte ) != 0x000001b6 )
            {
                /* not true , need to find the first VOP header */
                return AVIIF_KEYFRAME;
            }
            return p_byte[4] & 0xC0 ? 0 : AVIIF_KEYFRAME;

        default:
            /* I can't do it, so say yes */
            return AVIIF_KEYFRAME;
    }
}