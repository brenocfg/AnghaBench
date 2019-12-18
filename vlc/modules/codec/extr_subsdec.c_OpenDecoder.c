#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  scalar_t__ vlc_iconv_t ;
struct TYPE_13__ {char* psz_encoding; } ;
struct TYPE_14__ {int i_codec; TYPE_2__ subs; } ;
struct TYPE_12__ {scalar_t__ i_codec; } ;
struct TYPE_15__ {TYPE_3__ fmt_in; TYPE_1__ fmt_out; int /*<<< orphan*/  pf_decode; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_16__ {int i_align; scalar_t__ iconv_handle; int b_autodetect_utf8; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBlock ; 
#define  VLC_CODEC_ITU_T140 129 
#define  VLC_CODEC_SUBT 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ var_InheritBool (TYPE_4__*,char*) ; 
 int var_InheritInteger (TYPE_4__*,char*) ; 
 char* var_InheritString (TYPE_4__*,char*) ; 
 scalar_t__ vlc_iconv_open (char*,char const*) ; 
 char* vlc_pgettext (char*,char*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    switch( p_dec->fmt_in.i_codec )
    {
        case VLC_CODEC_SUBT:
        case VLC_CODEC_ITU_T140:
            break;
        default:
            return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    p_dec->p_sys = p_sys = calloc( 1, sizeof( *p_sys ) );
    if( p_sys == NULL )
        return VLC_ENOMEM;

    p_dec->pf_decode = DecodeBlock;
    p_dec->fmt_out.i_codec = 0;

    /* init of p_sys */
    p_sys->i_align = -1;
    p_sys->iconv_handle = (vlc_iconv_t)-1;
    p_sys->b_autodetect_utf8 = false;

    const char *encoding;
    char *var = NULL;

    /* First try demux-specified encoding */
    if( p_dec->fmt_in.i_codec == VLC_CODEC_ITU_T140 )
        encoding = "UTF-8"; /* IUT T.140 is always using UTF-8 */
    else
    if( p_dec->fmt_in.subs.psz_encoding && *p_dec->fmt_in.subs.psz_encoding )
    {
        encoding = p_dec->fmt_in.subs.psz_encoding;
        msg_Dbg (p_dec, "trying demuxer-specified character encoding: %s",
                 encoding);
    }
    else
    {
        /* Second, try configured encoding */
        if ((var = var_InheritString (p_dec, "subsdec-encoding")) != NULL)
        {
            msg_Dbg (p_dec, "trying configured character encoding: %s", var);
            if (!strcmp (var, "system"))
            {
                free (var);
                var = NULL;
                encoding = "";
                /* ^ iconv() treats "" as nl_langinfo(CODESET) */
            }
            else
                encoding = var;
        }
        else
        /* Third, try "local" encoding */
        {
        /* xgettext:
           The Windows ANSI code page most commonly used for this language.
           VLC uses this as a guess of the subtitle files character set
           (if UTF-8 and UTF-16 autodetection fails).
           Western European languages normally use "CP1252", which is a
           Microsoft-variant of ISO 8859-1. That suits the Latin alphabet.
           Other scripts use other code pages.

           This MUST be a valid iconv character set. If unsure, please refer
           the VideoLAN translators mailing list. */
            encoding = vlc_pgettext("GetACP", "CP1252");
            msg_Dbg (p_dec, "trying default character encoding: %s", encoding);
        }

        /* Check UTF-8 autodetection */
        if (var_InheritBool (p_dec, "subsdec-autodetect-utf8"))
        {
            msg_Dbg (p_dec, "using automatic UTF-8 detection");
            p_sys->b_autodetect_utf8 = true;
        }
    }

    if (strcasecmp (encoding, "UTF-8") && strcasecmp (encoding, "utf8"))
    {
        p_sys->iconv_handle = vlc_iconv_open ("UTF-8", encoding);
        if (p_sys->iconv_handle == (vlc_iconv_t)(-1))
            msg_Err (p_dec, "cannot convert from %s: %s", encoding,
                     vlc_strerror_c(errno));
    }
    free (var);

    p_sys->i_align = var_InheritInteger( p_dec, "subsdec-align" );

    return VLC_SUCCESS;
}