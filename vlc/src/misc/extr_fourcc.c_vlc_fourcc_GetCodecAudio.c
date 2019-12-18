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
typedef  scalar_t__ vlc_fourcc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 scalar_t__ VLC_CODEC_FL64 ; 
 scalar_t__ VLC_CODEC_S16B ; 
 scalar_t__ VLC_CODEC_S16L ; 
 scalar_t__ VLC_CODEC_S24B ; 
 scalar_t__ VLC_CODEC_S24L ; 
 scalar_t__ VLC_CODEC_S32B ; 
 scalar_t__ VLC_CODEC_S32L ; 
 scalar_t__ VLC_CODEC_S8 ; 
 scalar_t__ VLC_CODEC_U8 ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 scalar_t__ vlc_fourcc_GetCodec (int /*<<< orphan*/ ,scalar_t__) ; 

vlc_fourcc_t vlc_fourcc_GetCodecAudio( vlc_fourcc_t i_fourcc, int i_bits )
{
    const int i_bytes = ( i_bits + 7 ) / 8;

    if( i_fourcc == VLC_FOURCC( 'a', 'f', 'l', 't' ) )
    {
        switch( i_bytes )
        {
        case 4:
            return VLC_CODEC_FL32;
        case 8:
            return VLC_CODEC_FL64;
        default:
            return 0;
        }
    }
    else if( i_fourcc == VLC_FOURCC( 'a', 'r', 'a', 'w' ) )
    {
        switch( i_bytes )
        {
        case 1:
            return VLC_CODEC_U8;
        case 2:
            return VLC_CODEC_S16L;
        case 3:
            return VLC_CODEC_S24L;
        case 4:
            return VLC_CODEC_S32L;
        default:
            return 0;
        }
    }
    else if( i_fourcc == VLC_FOURCC( 't', 'w', 'o', 's' ) )
    {
        switch( i_bytes )
        {
        case 1:
            return VLC_CODEC_S8;
        case 2:
            return VLC_CODEC_S16B;
        case 3:
            return VLC_CODEC_S24B;
        case 4:
            return VLC_CODEC_S32B;
        default:
            return 0;
        }
    }
    else if( i_fourcc == VLC_FOURCC( 's', 'o', 'w', 't' ) )
    {
        switch( i_bytes )
        {
        case 1:
            return VLC_CODEC_S8;
        case 2:
            return VLC_CODEC_S16L;
        case 3:
            return VLC_CODEC_S24L;
        case 4:
            return VLC_CODEC_S32L;
        default:
            return 0;
        }
    }
    else
    {
        return vlc_fourcc_GetCodec( AUDIO_ES, i_fourcc );
    }
}