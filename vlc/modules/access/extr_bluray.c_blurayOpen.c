#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {int /*<<< orphan*/ * s; int /*<<< orphan*/  pf_demux; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * out; int /*<<< orphan*/  psz_filepath; TYPE_4__* p_sys; int /*<<< orphan*/  psz_url; } ;
typedef  TYPE_2__ vlc_object_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_2__ demux_t ;
struct TYPE_33__ {int /*<<< orphan*/  lock; } ;
struct TYPE_35__ {int i_cover_idx; int b_menu; int /*<<< orphan*/  p_parser; int /*<<< orphan*/ * p_out; int /*<<< orphan*/  p_tf_out; int /*<<< orphan*/  i_longest_title; int /*<<< orphan*/ * bluray; void* psz_bd_path; int /*<<< orphan*/  p_meta; int /*<<< orphan*/  read_block_lock; TYPE_1__ bdj; int /*<<< orphan*/  pl_info_lock; int /*<<< orphan*/  oldmouse; int /*<<< orphan*/  events_delayed; int /*<<< orphan*/  attachments; int /*<<< orphan*/  i_attachments; int /*<<< orphan*/  pp_title; int /*<<< orphan*/  i_title; scalar_t__ updates; int /*<<< orphan*/  i_still_end_time; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_36__ {int aacs_error_code; scalar_t__ num_bdj_titles; scalar_t__ num_hdmv_titles; scalar_t__ bdj_detected; int /*<<< orphan*/  libjvm_detected; int /*<<< orphan*/  bdj_handled; int /*<<< orphan*/  bdj_supported; int /*<<< orphan*/  bdplus_handled; int /*<<< orphan*/  libbdplus_detected; scalar_t__ bdplus_detected; int /*<<< orphan*/  aacs_handled; int /*<<< orphan*/  libaacs_detected; scalar_t__ aacs_detected; int /*<<< orphan*/  num_unsupported_titles; int /*<<< orphan*/  top_menu_supported; int /*<<< orphan*/  first_play_supported; int /*<<< orphan*/  bluray_detected; } ;
typedef  TYPE_5__ BLURAY_DISC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BDJO_IsBlacklisted (TYPE_2__*,void*) ; 
#define  BD_AACS_CERT_REVOKED 133 
#define  BD_AACS_CORRUPTED_DISC 132 
#define  BD_AACS_MMC_FAILED 131 
#define  BD_AACS_NO_CERT 130 
#define  BD_AACS_NO_CONFIG 129 
#define  BD_AACS_NO_PK 128 
 int /*<<< orphan*/  BLURAY_DEBUG_MASK ; 
 int /*<<< orphan*/  BLURAY_ERROR (char*) ; 
 int /*<<< orphan*/  BLURAY_PLAYER_SETTING_AUDIO_LANG ; 
 int /*<<< orphan*/  BLURAY_PLAYER_SETTING_MENU_LANG ; 
 int /*<<< orphan*/  BLURAY_PLAYER_SETTING_PG_LANG ; 
 int /*<<< orphan*/  BLURAY_PLAYER_SETTING_REGION_CODE ; 
 char* DemuxGetLanguageCode (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  FindMountPoint (void**) ; 
 char REGION_DEFAULT ; 
 int /*<<< orphan*/  STILL_IMAGE_NOT_SET ; 
 int /*<<< orphan*/  TAB_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_DIALOG_QUESTION_NORMAL ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_ETIMEOUT ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  attachThumbnail (TYPE_2__*) ; 
 int /*<<< orphan*/  bd_close (int /*<<< orphan*/ *) ; 
 TYPE_5__* bd_get_disc_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_get_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_get_meta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bd_init () ; 
 int /*<<< orphan*/ * bd_open (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_open_stream (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bd_play (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_register_argb_overlay_proc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_register_overlay_proc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_set_debug_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_set_debug_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_set_player_setting (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bd_set_player_setting_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  blurayArgbOverlayProc ; 
 int /*<<< orphan*/  blurayClose (TYPE_2__*) ; 
 int /*<<< orphan*/  blurayControl ; 
 int /*<<< orphan*/  blurayDemux ; 
 int /*<<< orphan*/  blurayInitTitles (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  blurayOverlayProc ; 
 int /*<<< orphan*/  blurayReadBlock ; 
 scalar_t__ bluraySetTitle (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bluray_DebugHandler ; 
 int /*<<< orphan*/ * esOutNew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  msg_Info (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  p_bluray_DebugObject ; 
 scalar_t__ probeFile (int /*<<< orphan*/ ) ; 
 scalar_t__ probeStream (TYPE_2__*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  timestamps_filter_es_out_New (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_Create (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int var_InheritBool (TYPE_2__*,char*) ; 
 void* var_InheritString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_SetBool (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  var_SetString (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  vlc_demux_chained_New (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (TYPE_2__*,char*,char*,char const*) ; 
 int vlc_dialog_wait_question (TYPE_2__*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  vlc_mouse_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_4__* vlc_obj_calloc (TYPE_2__*,int,int) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int blurayOpen(vlc_object_t *object)
{
    demux_t *p_demux = (demux_t*)object;
    demux_sys_t *p_sys;
    bool forced;
    uint64_t i_init_pos = 0;

    const char *error_msg = NULL;
#define BLURAY_ERROR(s) do { error_msg = s; goto error; } while(0)

    if (p_demux->out == NULL)
        return VLC_EGENERIC;

    forced = !strncasecmp(p_demux->psz_url, "bluray:", 7);

    if (p_demux->s) {
        if (!strncasecmp(p_demux->psz_url, "file:", 5)) {
            /* use access_demux for local files */
            return VLC_EGENERIC;
        }

        if (probeStream(p_demux) != VLC_SUCCESS) {
            return VLC_EGENERIC;
        }

    } else if (!forced) {
        if (!p_demux->psz_filepath) {
            return VLC_EGENERIC;
        }

        if (probeFile(p_demux->psz_filepath) != VLC_SUCCESS) {
            return VLC_EGENERIC;
        }
    }

    /* */
    p_demux->p_sys = p_sys = vlc_obj_calloc(object, 1, sizeof(*p_sys));
    if (unlikely(!p_sys))
        return VLC_ENOMEM;

    p_sys->i_still_end_time = STILL_IMAGE_NOT_SET;

    /* init demux info fields */
    p_sys->updates = 0;

    TAB_INIT(p_sys->i_title, p_sys->pp_title);
    TAB_INIT(p_sys->i_attachments, p_sys->attachments);
    ARRAY_INIT(p_sys->events_delayed);

    vlc_mouse_Init(&p_sys->oldmouse);

    vlc_mutex_init(&p_sys->pl_info_lock);
    vlc_mutex_init(&p_sys->bdj.lock);
    vlc_mutex_init(&p_sys->read_block_lock); /* used during bd_open_stream() */

    /* request sub demuxers to skip continuity check as some split
       file concatenation are just resetting counters... */
    var_Create( p_demux, "ts-cc-check", VLC_VAR_BOOL );
    var_SetBool( p_demux, "ts-cc-check", false );
    var_Create( p_demux, "ts-standard", VLC_VAR_STRING );
    var_SetString( p_demux, "ts-standard", "mpeg" );
    var_Create( p_demux, "ts-pmtfix-waitdata", VLC_VAR_BOOL );
    var_SetBool( p_demux, "ts-pmtfix-waitdata", false );
    var_Create( p_demux, "ts-patfix", VLC_VAR_BOOL );
    var_SetBool( p_demux, "ts-patfix", false );
    var_Create( p_demux, "ts-pcr-offsetfix", VLC_VAR_BOOL );
    var_SetBool( p_demux, "ts-pcr-offsetfix", false );

#ifdef DEBUG_BLURAY
    p_bluray_DebugObject = VLC_OBJECT(p_demux);
    bd_set_debug_mask(BLURAY_DEBUG_MASK);
    bd_set_debug_handler(bluray_DebugHandler);
#endif

    /* Open BluRay */
#ifdef BLURAY_DEMUX
    if (p_demux->s) {
        i_init_pos = vlc_stream_Tell(p_demux->s);

        p_sys->bluray = bd_init();
        if (!bd_open_stream(p_sys->bluray, p_demux, blurayReadBlock)) {
            bd_close(p_sys->bluray);
            p_sys->bluray = NULL;
        }
    } else
#endif
    {
        if (!p_demux->psz_filepath) {
            /* no path provided (bluray://). use default DVD device. */
            p_sys->psz_bd_path = var_InheritString(object, "dvd");
        } else {
            /* store current bd path */
            p_sys->psz_bd_path = strdup(p_demux->psz_filepath);
        }

        /* If we're passed a block device, try to convert it to the mount point. */
        FindMountPoint(&p_sys->psz_bd_path);

        p_sys->bluray = bd_open(p_sys->psz_bd_path, NULL);
    }
    if (!p_sys->bluray) {
        goto error;
    }

    /* Warning the user about AACS/BD+ */
    const BLURAY_DISC_INFO *disc_info = bd_get_disc_info(p_sys->bluray);

    /* Is it a bluray? */
    if (!disc_info->bluray_detected) {
        if (forced) {
            BLURAY_ERROR(_("Path doesn't appear to be a Blu-ray"));
        }
        goto error;
    }

    msg_Info(p_demux, "First play: %i, Top menu: %i\n"
                      "HDMV Titles: %i, BD-J Titles: %i, Other: %i",
             disc_info->first_play_supported, disc_info->top_menu_supported,
             disc_info->num_hdmv_titles, disc_info->num_bdj_titles,
             disc_info->num_unsupported_titles);

    /* AACS */
    if (disc_info->aacs_detected) {
        msg_Dbg(p_demux, "Disc is using AACS");
        if (!disc_info->libaacs_detected)
            BLURAY_ERROR(_("This Blu-ray Disc needs a library for AACS decoding"
                      ", and your system does not have it."));
        if (!disc_info->aacs_handled) {
            if (disc_info->aacs_error_code) {
                switch (disc_info->aacs_error_code) {
                case BD_AACS_CORRUPTED_DISC:
                    BLURAY_ERROR(_("Blu-ray Disc is corrupted."));
                case BD_AACS_NO_CONFIG:
                    BLURAY_ERROR(_("Missing AACS configuration file!"));
                case BD_AACS_NO_PK:
                    BLURAY_ERROR(_("No valid processing key found in AACS config file."));
                case BD_AACS_NO_CERT:
                    BLURAY_ERROR(_("No valid host certificate found in AACS config file."));
                case BD_AACS_CERT_REVOKED:
                    BLURAY_ERROR(_("AACS Host certificate revoked."));
                case BD_AACS_MMC_FAILED:
                    BLURAY_ERROR(_("AACS MMC failed."));
                }
            }
        }
    }

    /* BD+ */
    if (disc_info->bdplus_detected) {
        msg_Dbg(p_demux, "Disc is using BD+");
        if (!disc_info->libbdplus_detected)
            BLURAY_ERROR(_("This Blu-ray Disc needs a library for BD+ decoding"
                      ", and your system does not have it."));
        if (!disc_info->bdplus_handled)
            BLURAY_ERROR(_("Your system BD+ decoding library does not work. "
                      "Missing configuration?"));
    }

    /* set player region code */
    char *psz_region = var_InheritString(p_demux, "bluray-region");
    unsigned int region = psz_region ? (psz_region[0] - 'A') : REGION_DEFAULT;
    free(psz_region);
    bd_set_player_setting(p_sys->bluray, BLURAY_PLAYER_SETTING_REGION_CODE, 1<<region);

    /* set preferred languages */
    const char *psz_code = DemuxGetLanguageCode( p_demux, "audio-language" );
    bd_set_player_setting_str(p_sys->bluray, BLURAY_PLAYER_SETTING_AUDIO_LANG, psz_code);
    psz_code = DemuxGetLanguageCode( p_demux, "sub-language" );
    bd_set_player_setting_str(p_sys->bluray, BLURAY_PLAYER_SETTING_PG_LANG,    psz_code);
    psz_code = DemuxGetLanguageCode( p_demux, "menu-language" );
    bd_set_player_setting_str(p_sys->bluray, BLURAY_PLAYER_SETTING_MENU_LANG,  psz_code);

    /* Get disc metadata */
    p_sys->p_meta = bd_get_meta(p_sys->bluray);
    if (!p_sys->p_meta)
        msg_Warn(p_demux, "Failed to get meta info.");

    p_sys->i_cover_idx = -1;
    attachThumbnail(p_demux);

    p_sys->b_menu = var_InheritBool(p_demux, "bluray-menu");

    /* Check BD-J capability */
    if (p_sys->b_menu && disc_info->bdj_detected && !disc_info->bdj_handled) {
        msg_Err(p_demux, "BD-J menus not supported. Playing without menus. "
                "BD-J support: %d, JVM found: %d, JVM usable: %d",
                disc_info->bdj_supported, disc_info->libjvm_detected, disc_info->bdj_handled);
        vlc_dialog_display_error(p_demux, _("Java required"),
             _("This Blu-ray disc requires Java for menus support.%s\nThe disc will be played without menus."),
             !disc_info->libjvm_detected ? _("Java was not found on your system.") : "");
        p_sys->b_menu = false;
    }

    if(disc_info->bdj_detected &&p_sys->b_menu &&
       BDJO_IsBlacklisted(p_demux, p_sys->psz_bd_path))
    {
        p_sys->b_menu = vlc_dialog_wait_question( p_demux,
                                                  VLC_DIALOG_QUESTION_NORMAL,
                                                  _("Play without Menus"),
                                                  _("Try anyway"),
                                                  NULL,
                                                  _("BDJO Menu check"),
                                                  "%s",
                                                  _("Incompatible Java Menu detected"));
    }

    /* Get titles and chapters */
    blurayInitTitles(p_demux, disc_info->num_hdmv_titles + disc_info->num_bdj_titles + 1/*Top Menu*/ + 1/*First Play*/);

    /*
     * Initialize the event queue, so we can receive events in blurayDemux(Menu).
     */
    bd_get_event(p_sys->bluray, NULL);

    /* Registering overlay event handler */
    bd_register_overlay_proc(p_sys->bluray, p_demux, blurayOverlayProc);

    if (p_sys->b_menu) {

        /* Register ARGB overlay handler for BD-J */
        if (disc_info->num_bdj_titles)
            bd_register_argb_overlay_proc(p_sys->bluray, p_demux, blurayArgbOverlayProc, NULL);

        /* libbluray will start playback from "First-Title" title */
        if (bd_play(p_sys->bluray) == 0)
            BLURAY_ERROR(_("Failed to start bluray playback. Please try without menu support."));

    } else {
        /* set start title number */
        if (bluraySetTitle(p_demux, p_sys->i_longest_title) != VLC_SUCCESS) {
            msg_Err(p_demux, "Could not set the title %d", p_sys->i_longest_title);
            goto error;
        }
    }

    p_sys->p_tf_out = timestamps_filter_es_out_New(p_demux->out);
    if(unlikely(!p_sys->p_tf_out))
        goto error;

    p_sys->p_out = esOutNew(VLC_OBJECT(p_demux), p_sys->p_tf_out, p_demux);
    if (unlikely(p_sys->p_out == NULL))
        goto error;

    p_sys->p_parser = vlc_demux_chained_New(VLC_OBJECT(p_demux), "ts", p_sys->p_out);
    if (!p_sys->p_parser) {
        msg_Err(p_demux, "Failed to create TS demuxer");
        goto error;
    }

    p_demux->pf_control = blurayControl;
    p_demux->pf_demux   = blurayDemux;

    return VLC_SUCCESS;

error:
    if (error_msg)
        vlc_dialog_display_error(p_demux, _("Blu-ray error"), "%s", error_msg);
    blurayClose(object);

    if (p_demux->s != NULL) {
        /* restore stream position */
        if (vlc_stream_Seek(p_demux->s, i_init_pos) != VLC_SUCCESS) {
            msg_Err(p_demux, "Failed to seek back to stream start");
            return VLC_ETIMEOUT;
        }
    }

    return VLC_EGENERIC;
#undef BLURAY_ERROR
}