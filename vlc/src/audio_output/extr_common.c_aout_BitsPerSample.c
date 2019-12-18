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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
#define  VLC_CODEC_ALAW 149 
#define  VLC_CODEC_F32B 148 
#define  VLC_CODEC_F32L 147 
#define  VLC_CODEC_F64B 146 
#define  VLC_CODEC_F64L 145 
#define  VLC_CODEC_MULAW 144 
#define  VLC_CODEC_S16B 143 
#define  VLC_CODEC_S16L 142 
#define  VLC_CODEC_S24B 141 
#define  VLC_CODEC_S24B32 140 
#define  VLC_CODEC_S24L 139 
#define  VLC_CODEC_S24L32 138 
#define  VLC_CODEC_S32B 137 
#define  VLC_CODEC_S32L 136 
#define  VLC_CODEC_S8 135 
#define  VLC_CODEC_U16B 134 
#define  VLC_CODEC_U16L 133 
#define  VLC_CODEC_U24B 132 
#define  VLC_CODEC_U24L 131 
#define  VLC_CODEC_U32B 130 
#define  VLC_CODEC_U32L 129 
#define  VLC_CODEC_U8 128 
 int vlc_fourcc_GetCodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int aout_BitsPerSample( vlc_fourcc_t i_format )
{
    switch( vlc_fourcc_GetCodec( AUDIO_ES, i_format ) )
    {
    case VLC_CODEC_U8:
    case VLC_CODEC_S8:
    case VLC_CODEC_ALAW:
    case VLC_CODEC_MULAW:
        return 8;

    case VLC_CODEC_U16L:
    case VLC_CODEC_S16L:
    case VLC_CODEC_U16B:
    case VLC_CODEC_S16B:
        return 16;

    case VLC_CODEC_U24L:
    case VLC_CODEC_S24L:
    case VLC_CODEC_U24B:
    case VLC_CODEC_S24B:
        return 24;

    case VLC_CODEC_S24L32:
    case VLC_CODEC_S24B32:
    case VLC_CODEC_U32L:
    case VLC_CODEC_U32B:
    case VLC_CODEC_S32L:
    case VLC_CODEC_S32B:
    case VLC_CODEC_F32L:
    case VLC_CODEC_F32B:
        return 32;

    case VLC_CODEC_F64L:
    case VLC_CODEC_F64B:
        return 64;

    default:
        /* For these formats the caller has to indicate the parameters
         * by hand. */
        return 0;
    }
}