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

/* Variables and functions */
 size_t __MIN (size_t,unsigned int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

bool OMXCodec_IsBlacklisted( const char *p_name, unsigned int i_name_len )
{
    static const char *blacklisted_prefix[] = {
        /* ignore OpenCore software codecs */
        "OMX.PV.",
        /* The same sw codecs, renamed in ICS (perhaps also in honeycomb) */
        "OMX.google.",
        /* This one has been seen on HTC One V - it behaves like it works,
         * but FillBufferDone returns buffers filled with 0 bytes. The One V
         * has got a working OMX.qcom.video.decoder.avc instead though. */
        "OMX.ARICENT.",
        /* Use VC1 decoder for WMV3 for now */
        "OMX.SEC.WMV.Decoder",
        /* This decoder does work, but has an insane latency (leading to errors
         * about "main audio output playback way too late" and dropped frames).
         * At least Samsung Galaxy S III (where this decoder is present) has
         * got another one, OMX.SEC.mp3.dec, that works well and has a
         * sensible latency. (Also, even if that one isn't found, in general,
         * using SW codecs is usually more than fast enough for MP3.) */
        "OMX.SEC.MP3.Decoder",
        /* black screen */
        "OMX.MTK.VIDEO.DECODER.VC1",
        /* Not working or crashing (Samsung) */
        "OMX.SEC.vp8.dec",
        NULL
    };

    static const char *blacklisted_suffix[] = {
        /* Codecs with DRM, that don't output plain YUV data but only
         * support direct rendering where the output can't be intercepted. */
        ".secure",
        /* Samsung sw decoders */
        ".sw.dec",
        NULL
    };

    /* p_name is not '\0' terminated */

    for( const char **pp_bl_prefix = blacklisted_prefix; *pp_bl_prefix != NULL;
          pp_bl_prefix++ )
    {
        if( !strncmp( p_name, *pp_bl_prefix,
           __MIN( strlen(*pp_bl_prefix), i_name_len ) ) )
           return true;
    }

    for( const char **pp_bl_suffix = blacklisted_suffix; *pp_bl_suffix != NULL;
         pp_bl_suffix++ )
    {
       size_t i_suffix_len = strlen( *pp_bl_suffix );

       if( i_name_len > i_suffix_len
        && !strncmp( p_name + i_name_len - i_suffix_len, *pp_bl_suffix,
                     i_suffix_len ) )
           return true;
    }

    return false;
}