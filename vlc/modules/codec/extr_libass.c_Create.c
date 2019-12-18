#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;
struct TYPE_18__ {char* psz_mime; char* psz_name; int /*<<< orphan*/  i_data; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_3__ input_attachment_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_16__ {scalar_t__ i_codec; int /*<<< orphan*/  i_extra; int /*<<< orphan*/  p_extra; } ;
struct TYPE_19__ {TYPE_2__ fmt_out; TYPE_1__ fmt_in; TYPE_5__* p_sys; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_20__ {int i_refcount; int /*<<< orphan*/ * p_library; int /*<<< orphan*/ * p_track; int /*<<< orphan*/ * p_renderer; int /*<<< orphan*/  i_max_stop; int /*<<< orphan*/  fmt; int /*<<< orphan*/  lock; } ;
typedef  TYPE_5__ decoder_sys_t ;
typedef  int /*<<< orphan*/  ASS_Track ;
typedef  int /*<<< orphan*/  ASS_Renderer ;
typedef  int /*<<< orphan*/  ASS_Library ;

/* Variables and functions */
 int /*<<< orphan*/  ASS_FONTPROVIDER_AUTODETECT ; 
 int /*<<< orphan*/  ASS_HINTING_NONE ; 
 int /*<<< orphan*/  DecSysRelease (TYPE_5__*) ; 
 int /*<<< orphan*/  DecodeBlock ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  VLC_CODEC_RGBA ; 
 scalar_t__ VLC_CODEC_SSA ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  _ (char*) ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_add_font (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ass_library_init () ; 
 int /*<<< orphan*/ * ass_new_track (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_process_codec_private (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ass_renderer_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_set_extract_fonts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ass_set_font_scale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ass_set_fonts (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ass_set_hinting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ass_set_line_spacing (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  ass_set_style_overrides (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ass_set_use_margins (int /*<<< orphan*/ *,int) ; 
 scalar_t__ decoder_GetInputAttachments (TYPE_4__*,TYPE_3__***,int*) ; 
 int /*<<< orphan*/  free (TYPE_3__**) ; 
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * vlc_dialog_display_progress (TYPE_4__*,int,double,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dialog_release (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Create( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t *)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_SSA )
        return VLC_EGENERIC;

    p_dec->pf_decode = DecodeBlock;
    p_dec->pf_flush  = Flush;

    p_dec->p_sys = p_sys = malloc( sizeof( decoder_sys_t ) );
    if( !p_sys )
        return VLC_ENOMEM;

    /* */
    vlc_mutex_init( &p_sys->lock );
    p_sys->i_refcount = 1;
    memset( &p_sys->fmt, 0, sizeof(p_sys->fmt) );
    p_sys->i_max_stop = VLC_TICK_INVALID;
    p_sys->p_library  = NULL;
    p_sys->p_renderer = NULL;
    p_sys->p_track    = NULL;

    /* Create libass library */
    ASS_Library *p_library = p_sys->p_library = ass_library_init();
    if( !p_library )
    {
        msg_Warn( p_dec, "Libass library creation failed" );
        DecSysRelease( p_sys );
        return VLC_EGENERIC;
    }

    /* load attachments */
    input_attachment_t  **pp_attachments;
    int                   i_attachments;
    if( decoder_GetInputAttachments( p_dec, &pp_attachments, &i_attachments ))
    {
        i_attachments = 0;
        pp_attachments = NULL;
    }
    for( int k = 0; k < i_attachments; k++ )
    {
        input_attachment_t *p_attach = pp_attachments[k];

        bool found = false;

        /* Check mimetype*/
        if( !strcasecmp( p_attach->psz_mime, "application/x-truetype-font" ) )
            found = true;
        /* Then extension */
        else if( !found && strlen( p_attach->psz_name ) > 4 )
        {
            char *ext = p_attach->psz_name + strlen( p_attach->psz_name ) - 4;

            if( !strcasecmp( ext, ".ttf" ) || !strcasecmp( ext, ".otf" ) || !strcasecmp( ext, ".ttc" ) )
                found = true;
        }

        if( found )
        {
            msg_Dbg( p_dec, "adding embedded font %s", p_attach->psz_name );

            ass_add_font( p_sys->p_library, p_attach->psz_name, p_attach->p_data, p_attach->i_data );
        }
        vlc_input_attachment_Delete( p_attach );
    }
    free( pp_attachments );

    ass_set_extract_fonts( p_library, true );
    ass_set_style_overrides( p_library, NULL );

    /* Create the renderer */
    ASS_Renderer *p_renderer = p_sys->p_renderer = ass_renderer_init( p_library );
    if( !p_renderer )
    {
        msg_Warn( p_dec, "Libass renderer creation failed" );
        DecSysRelease( p_sys );
        return VLC_EGENERIC;
    }

    ass_set_use_margins( p_renderer, false);
    //if( false )
    //    ass_set_margins( p_renderer, int t, int b, int l, int r);
    ass_set_font_scale( p_renderer, 1.0 );
    ass_set_line_spacing( p_renderer, 0.0 );

#if defined( __ANDROID__ )
    const char *psz_font, *psz_family;
    const char *psz_font_droid = "/system/fonts/DroidSans-Bold.ttf";
    const char *psz_family_droid = "Droid Sans Bold";
    const char *psz_font_noto = "/system/fonts/NotoSansCJK-Regular.ttc";
    const char *psz_family_noto = "Noto Sans";

    // Workaround for Android 5.0+, since libass doesn't parse the XML yet
    if( access( psz_font_noto, R_OK ) != -1 )
    {
        psz_font = psz_font_noto;
        psz_family = psz_family_noto;
    }
    else
    {
        psz_font = psz_font_droid;
        psz_family = psz_family_droid;
    }

#elif defined( __APPLE__ )
    const char *psz_font = NULL; /* We don't ship a default font with VLC */
    const char *psz_family = "Helvetica Neue"; /* Use HN if we can't find anything more suitable - Arial is not on all Apple platforms */
#else
    const char *psz_font = NULL; /* We don't ship a default font with VLC */
    const char *psz_family = "Arial"; /* Use Arial if we can't find anything more suitable */
#endif

#ifdef HAVE_FONTCONFIG
#if defined(_WIN32)
    vlc_dialog_id *p_dialog_id =
        vlc_dialog_display_progress( p_dec, true, 0.0, NULL,
                                    _("Building font cache"),
                                    _( "Please wait while your font cache is rebuilt.\n"
                                    "This should take less than a minute." ) );
#endif
    ass_set_fonts( p_renderer, psz_font, psz_family, ASS_FONTPROVIDER_AUTODETECT, NULL, 1 );  // setup default font/family
#if defined(_WIN32)
    if( p_dialog_id != 0 )
        vlc_dialog_release( p_dec, p_dialog_id );
#endif
#else
    ass_set_fonts( p_renderer, psz_font, psz_family, ASS_FONTPROVIDER_AUTODETECT, NULL, 0 );
#endif

    /* Anything else than NONE will break smooth img updating.
       TODO: List and force ASS_HINTING_LIGHT for known problematic fonts */
    ass_set_hinting( p_renderer, ASS_HINTING_NONE );

    /* Add a track */
    ASS_Track *p_track = p_sys->p_track = ass_new_track( p_sys->p_library );
    if( !p_track )
    {
        DecSysRelease( p_sys );
        return VLC_EGENERIC;
    }
    ass_process_codec_private( p_track, p_dec->fmt_in.p_extra, p_dec->fmt_in.i_extra );

    p_dec->fmt_out.i_codec = VLC_CODEC_RGBA;

    return VLC_SUCCESS;
}