#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ i_codec; int /*<<< orphan*/  i_cat; } ;
typedef  TYPE_1__ es_format_t ;
typedef  int /*<<< orphan*/  decoder_t ;

/* Variables and functions */
 char* N_ (char*) ; 
 scalar_t__ VLC_CODEC_UNKNOWN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* vlc_fourcc_GetDescription (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void DecoderUnsupportedCodec( decoder_t *p_dec, const es_format_t *fmt, bool b_decoding )
{
    if (fmt->i_codec != VLC_CODEC_UNKNOWN && fmt->i_codec) {
        const char *desc = vlc_fourcc_GetDescription(fmt->i_cat, fmt->i_codec);
        if (!desc || !*desc)
            desc = N_("No description for this codec");
        msg_Err( p_dec, "Codec `%4.4s' (%s) is not supported.", (char*)&fmt->i_codec, desc );
        vlc_dialog_display_error( p_dec, _("Codec not supported"),
            _("VLC could not decode the format \"%4.4s\" (%s)"),
            (char*)&fmt->i_codec, desc );
    } else if( b_decoding ){
        msg_Err( p_dec, "could not identify codec" );
        vlc_dialog_display_error( p_dec, _("Unidentified codec"),
            _("VLC could not identify the audio or video codec" ) );
    }
}