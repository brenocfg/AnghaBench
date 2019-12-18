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
struct str2quirks {char* member_0; int member_1; char* psz_name; int i_quirks; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int AUDIO_ES ; 
#define  OMXCODEC_AUDIO_QUIRKS_NEED_CHANNELS 135 
 int OMXCODEC_NO_QUIRKS ; 
#define  OMXCODEC_QUIRKS_NEED_CSD 134 
#define  OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING 133 
#define  OMXCODEC_VIDEO_QUIRKS_SUPPORT_INTERLACED 132 
 int VIDEO_ES ; 
#define  VLC_CODEC_H264 131 
#define  VLC_CODEC_MP4A 130 
#define  VLC_CODEC_VC1 129 
#define  VLC_CODEC_VORBIS 128 
 size_t __MIN (size_t,unsigned int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

int OMXCodec_GetQuirks( enum es_format_category_e i_cat, vlc_fourcc_t i_codec,
                        const char *p_name, unsigned int i_name_len )
{
    static const struct str2quirks quirks_prefix[] = {
        { "OMX.MTK.VIDEO.DECODER.MPEG4", OMXCODEC_QUIRKS_NEED_CSD },
        { "OMX.Marvell", OMXCODEC_AUDIO_QUIRKS_NEED_CHANNELS },

        /* The list of decoders that signal padding properly is not necessary,
         * since that is the default, but keep it here for reference. (This is
         * only relevant for manufacturers that are known to have decoders with
         * this kind of bug.)
         * static const char *padding_decoders[] = {
         *    "OMX.SEC.AVC.Decoder",
         *    "OMX.SEC.wmv7.dec",
         *    "OMX.SEC.wmv8.dec",
         *     NULL
         * };
         */
        { "OMX.SEC.avc.dec", OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING },
        { "OMX.SEC.avcdec", OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING },
        { "OMX.SEC.MPEG4.Decoder", OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING },
        { "OMX.SEC.mpeg4.dec", OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING },
        { "OMX.SEC.vc1.dec", OMXCODEC_VIDEO_QUIRKS_IGNORE_PADDING },
        { "OMX.amlogic.avc.decoder.awesome", OMXCODEC_VIDEO_QUIRKS_SUPPORT_INTERLACED },
        { NULL, 0 }
    };

    static struct str2quirks quirks_suffix[] = {
        { NULL, 0 }
    };

    int i_quirks = OMXCODEC_NO_QUIRKS;

    if( i_cat == VIDEO_ES )
    {
        switch( i_codec )
        {
        case VLC_CODEC_H264:
        case VLC_CODEC_VC1:
            i_quirks |= OMXCODEC_QUIRKS_NEED_CSD;
            break;
        }
    } else if( i_cat == AUDIO_ES )
    {
        switch( i_codec )
        {
        case VLC_CODEC_VORBIS:
        case VLC_CODEC_MP4A:
            i_quirks |= OMXCODEC_QUIRKS_NEED_CSD;
            break;
        }
    }

    /* p_name is not '\0' terminated */

    for( const struct str2quirks *p_q_prefix = quirks_prefix; p_q_prefix->psz_name;
         p_q_prefix++ )
    {
        const char *psz_prefix = p_q_prefix->psz_name;
        if( !strncmp( p_name, psz_prefix,
           __MIN( strlen(psz_prefix), i_name_len ) ) )
           i_quirks |= p_q_prefix->i_quirks;
    }

    for( const struct str2quirks *p_q_suffix = quirks_suffix; p_q_suffix->psz_name;
         p_q_suffix++ )
    {
        const char *psz_suffix = p_q_suffix->psz_name;
        size_t i_suffix_len = strlen( psz_suffix );

        if( i_name_len > i_suffix_len
         && !strncmp( p_name + i_name_len - i_suffix_len, psz_suffix,
                      i_suffix_len ) )
           i_quirks |= p_q_suffix->i_quirks;
    }

    return i_quirks;
}