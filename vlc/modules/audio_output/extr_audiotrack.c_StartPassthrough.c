#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ audio_output_t ;
struct TYPE_14__ {int i_format; int i_rate; int i_bytes_per_frame; int i_frame_length; int i_channels; void* i_physical_channels; } ;
struct TYPE_12__ {int b_passthrough; scalar_t__ i_chans_to_reorder; TYPE_6__ fmt; } ;
typedef  TYPE_3__ aout_sys_t ;
struct TYPE_10__ {int ENCODING_IEC61937; int ENCODING_AC3; int ENCODING_E_AC3; int ENCODING_DTS; int /*<<< orphan*/  has_ENCODING_DTS; int /*<<< orphan*/  has_ENCODING_E_AC3; int /*<<< orphan*/  has_ENCODING_AC3; scalar_t__ has_ENCODING_IEC61937; } ;
struct TYPE_13__ {TYPE_1__ AudioFormat; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 void* AOUT_CHANS_7_1 ; 
 void* AOUT_CHANS_STEREO ; 
 int AudioTrack_Create (int /*<<< orphan*/ *,TYPE_2__*,int,int,void*) ; 
 int /*<<< orphan*/  AudioTrack_HasEncoding (TYPE_2__*,int) ; 
#define  VLC_CODEC_A52 133 
#define  VLC_CODEC_DTS 132 
#define  VLC_CODEC_DTSHD 131 
#define  VLC_CODEC_EAC3 130 
#define  VLC_CODEC_MLP 129 
 int VLC_CODEC_SPDIFB ; 
 int VLC_CODEC_SPDIFL ; 
#define  VLC_CODEC_TRUEHD 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int aout_FormatNbChannels (TYPE_6__*) ; 
 TYPE_5__ jfields ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 

__attribute__((used)) static int
StartPassthrough( JNIEnv *env, audio_output_t *p_aout )
{
    aout_sys_t *p_sys = p_aout->sys;
    int i_at_format;

    if( !AudioTrack_HasEncoding( p_aout, p_sys->fmt.i_format ) )
        return VLC_EGENERIC;

    if( jfields.AudioFormat.has_ENCODING_IEC61937 )
    {
        i_at_format = jfields.AudioFormat.ENCODING_IEC61937;
        switch( p_sys->fmt.i_format )
        {
            case VLC_CODEC_TRUEHD:
            case VLC_CODEC_MLP:
                p_sys->fmt.i_rate = 192000;
                p_sys->fmt.i_bytes_per_frame = 16;

                /* AudioFormat.ENCODING_IEC61937 documentation says that the
                 * channel layout must be stereo. Well, not for TrueHD
                 * apparently */
                p_sys->fmt.i_physical_channels = AOUT_CHANS_7_1;
                break;
            case VLC_CODEC_DTS:
                p_sys->fmt.i_bytes_per_frame = 4;
                p_sys->fmt.i_physical_channels = AOUT_CHANS_STEREO;
                break;
            case VLC_CODEC_DTSHD:
                p_sys->fmt.i_bytes_per_frame = 4;
                p_sys->fmt.i_physical_channels = AOUT_CHANS_STEREO;
                p_sys->fmt.i_rate = 192000;
                p_sys->fmt.i_bytes_per_frame = 16;
                break;
            case VLC_CODEC_EAC3:
                p_sys->fmt.i_rate = 192000;
            case VLC_CODEC_A52:
                p_sys->fmt.i_physical_channels = AOUT_CHANS_STEREO;
                p_sys->fmt.i_bytes_per_frame = 4;
                break;
            default:
                return VLC_EGENERIC;
        }
        p_sys->fmt.i_frame_length = 1;
        p_sys->fmt.i_channels = aout_FormatNbChannels( &p_sys->fmt );
        p_sys->fmt.i_format = VLC_CODEC_SPDIFL;
    }
    else
    {
        switch( p_sys->fmt.i_format )
        {
            case VLC_CODEC_A52:
                if( !jfields.AudioFormat.has_ENCODING_AC3 )
                    return VLC_EGENERIC;
                i_at_format = jfields.AudioFormat.ENCODING_AC3;
                break;
            case VLC_CODEC_EAC3:
                if( !jfields.AudioFormat.has_ENCODING_E_AC3 )
                    return VLC_EGENERIC;
                i_at_format = jfields.AudioFormat.ENCODING_E_AC3;
                break;
            case VLC_CODEC_DTS:
                if( !jfields.AudioFormat.has_ENCODING_DTS )
                    return VLC_EGENERIC;
                i_at_format = jfields.AudioFormat.ENCODING_DTS;
                break;
            default:
                return VLC_EGENERIC;
        }
        p_sys->fmt.i_bytes_per_frame = 4;
        p_sys->fmt.i_frame_length = 1;
        p_sys->fmt.i_physical_channels = AOUT_CHANS_STEREO;
        p_sys->fmt.i_channels = 2;
        p_sys->fmt.i_format = VLC_CODEC_SPDIFB;
    }

    int i_ret = AudioTrack_Create( env, p_aout, p_sys->fmt.i_rate, i_at_format,
                                   p_sys->fmt.i_physical_channels );
    if( i_ret != VLC_SUCCESS )
        msg_Warn( p_aout, "SPDIF configuration failed" );
    else
    {
        p_sys->b_passthrough = true;
        p_sys->i_chans_to_reorder = 0;
    }

    return i_ret;
}