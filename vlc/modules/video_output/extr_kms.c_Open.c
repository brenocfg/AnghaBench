#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  (* close ) (TYPE_1__*) ;int /*<<< orphan*/  control; int /*<<< orphan*/  display; int /*<<< orphan*/ * prepare; int /*<<< orphan*/  pool; TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_15__ {int forced_drm_fourcc; scalar_t__ vlc_fourcc; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  drm_fourcc; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_16__ {scalar_t__ i_chroma; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_3__ video_format_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  Close (TYPE_1__*) ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  Display ; 
 scalar_t__ OpenDisplay (TYPE_1__*) ; 
 int /*<<< orphan*/  Pool ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  video_format_ApplyRotation (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ vlc_fourcc_GetCodecFromString (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* vlc_obj_calloc (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ vout_display_cfg_IsWindowed (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int Open(vout_display_t *vd, const vout_display_cfg_t *cfg,
                video_format_t *fmtp, vlc_video_context *context)
{
    vout_display_sys_t *sys;
    vlc_fourcc_t local_vlc_chroma;
    uint32_t local_drm_chroma;
    video_format_t fmt = {};
    char *chroma;

    if (vout_display_cfg_IsWindowed(cfg))
        return VLC_EGENERIC;

    /*
     * Allocate instance and initialize some members
     */
    vd->sys = sys = vlc_obj_calloc(VLC_OBJECT(vd), 1, sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;

    chroma = var_InheritString(vd, "kms-vlc-chroma");
    if (chroma) {
        local_vlc_chroma = vlc_fourcc_GetCodecFromString(VIDEO_ES, chroma);

        if (local_vlc_chroma) {
            sys->vlc_fourcc = local_vlc_chroma;
            msg_Dbg(vd, "Forcing VLC to use chroma '%4s'", chroma);
         } else {
            sys->vlc_fourcc = fmtp->i_chroma;
            msg_Dbg(vd, "Chroma %4s invalid, using default", chroma);
         }

        free(chroma);
        chroma = NULL;
    } else {
        sys->vlc_fourcc = fmtp->i_chroma;
        msg_Dbg(vd, "Chroma not defined, using default");
    }

    chroma = var_InheritString(vd, "kms-drm-chroma");
    if (chroma) {
        local_drm_chroma = VLC_FOURCC(chroma[0], chroma[1], chroma[2],
                                      chroma[3]);

        if (local_drm_chroma) {
            sys->forced_drm_fourcc = true;
            sys->drm_fourcc = local_drm_chroma;
            msg_Dbg(vd, "Setting DRM chroma to '%4s'", chroma);
        }
        else
            msg_Dbg(vd, "Chroma %4s invalid, using default", chroma);

        free(chroma);
        chroma = NULL;
    }

    if (OpenDisplay(vd) != VLC_SUCCESS) {
        Close(vd);
        return VLC_EGENERIC;
    }

    video_format_ApplyRotation(&fmt, fmtp);

    fmt.i_width = fmt.i_visible_width  = sys->width;
    fmt.i_height = fmt.i_visible_height = sys->height;
    fmt.i_chroma = sys->vlc_fourcc;
    *fmtp = fmt;

    vd->pool    = Pool;
    vd->prepare = NULL;
    vd->display = Display;
    vd->control = Control;
    vd->close = Close;

    (void) context;
    return VLC_SUCCESS;
}