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
typedef  int uint8_t ;

/* Variables and functions */
 int PROFILE_DTS_EXPRESS ; 
 int PROFILE_DTS_HD ; 
 int /*<<< orphan*/  VLC_CODEC_A52 ; 
 int /*<<< orphan*/  VLC_CODEC_ALS ; 
 int /*<<< orphan*/  VLC_CODEC_DIRAC ; 
 int /*<<< orphan*/  VLC_CODEC_DTS ; 
 int /*<<< orphan*/  VLC_CODEC_EAC3 ; 
 int /*<<< orphan*/  VLC_CODEC_H264 ; 
 int /*<<< orphan*/  VLC_CODEC_JPEG ; 
 int /*<<< orphan*/  VLC_CODEC_MP4A ; 
 int /*<<< orphan*/  VLC_CODEC_MP4V ; 
 int /*<<< orphan*/  VLC_CODEC_MPGA ; 
 int /*<<< orphan*/  VLC_CODEC_MPGV ; 
 int /*<<< orphan*/  VLC_CODEC_PNG ; 
 int /*<<< orphan*/  VLC_CODEC_VC1 ; 
 int /*<<< orphan*/  VLC_CODEC_VORBIS ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 

__attribute__((used)) static inline bool MPEG4_Codec_By_ObjectType(uint8_t oti,
                                              const uint8_t *p_dsi,
                                              size_t i_dsi,
                                              vlc_fourcc_t *pi_codec,
                                              int *pi_profile)
{
    /* See 14496-1 and http://mp4ra.org/#/object_types */
    switch(oti)
    {
        case 0x20: /* MPEG4 VIDEO */
            *pi_codec = VLC_CODEC_MP4V;
            break;
        case 0x21: /* H.264 */
            *pi_codec = VLC_CODEC_H264;
            break;
        case 0x40:
        case 0x41:
            *pi_codec = VLC_CODEC_MP4A;
            if(i_dsi >= 2 && p_dsi[0] == 0xF8 && (p_dsi[1]&0xE0)== 0x80)
                *pi_codec = VLC_CODEC_ALS;
            break;
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65: /* MPEG2 video */
            *pi_codec = VLC_CODEC_MPGV;
            break;
            /* Theses are MPEG2-AAC */
        case 0x66: /* main profile */
        case 0x67: /* Low complexity profile */
        case 0x68: /* Scaleable Sampling rate profile */
            *pi_codec = VLC_CODEC_MP4A;
            break;
            /* True MPEG 2 audio */
        case 0x69:
            *pi_codec = VLC_CODEC_MPGA;
            break;
        case 0x6a: /* MPEG1 video */
            *pi_codec = VLC_CODEC_MPGV;
            break;
        case 0x6b: /* MPEG1 audio */
            *pi_codec = VLC_CODEC_MPGA;
            break;
        case 0x6c: /* jpeg */
            *pi_codec = VLC_CODEC_JPEG;
            break;
        case 0x6d: /* png */
            *pi_codec = VLC_CODEC_PNG;
            break;
        case 0x6e: /* jpeg2000 */
            *pi_codec = VLC_FOURCC('M','J','2','C');
            break;
        case 0xa3: /* vc1 */
            *pi_codec = VLC_CODEC_VC1;
            break;
        case 0xa4:
            *pi_codec = VLC_CODEC_DIRAC;
            break;
        case 0xa5:
            *pi_codec = VLC_CODEC_A52;
            break;
        case 0xa6:
            *pi_codec = VLC_CODEC_EAC3;
            break;
        case 0xa9: /* dts */
            *pi_codec = VLC_CODEC_DTS;
            break;
        case 0xaa: /* DTS-HD HRA */
        case 0xab: /* DTS-HD Master Audio */
            *pi_profile = PROFILE_DTS_HD;
            *pi_codec = VLC_CODEC_DTS;
            break;
        case 0xac: /* Extension Substream containing only LBR */
            *pi_profile = PROFILE_DTS_EXPRESS;
            *pi_codec = VLC_CODEC_DTS;
            break;
        case 0xDD:
            *pi_codec = VLC_CODEC_VORBIS;
            break;
        default:
            return false;
    }
    return true;
}