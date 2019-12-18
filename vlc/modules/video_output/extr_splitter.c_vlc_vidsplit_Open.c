#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  (* close ) (TYPE_1__*) ;int /*<<< orphan*/  control; int /*<<< orphan*/  display; int /*<<< orphan*/  prepare; int /*<<< orphan*/  source; TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_21__ {int i_output; TYPE_5__* p_output; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * p_module; } ;
struct TYPE_19__ {struct vlc_vidsplit_part* parts; int /*<<< orphan*/ * pictures; int /*<<< orphan*/  lock; TYPE_4__ splitter; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct TYPE_20__ {int is_display_filled; int /*<<< orphan*/ * window; int /*<<< orphan*/  zoom; int /*<<< orphan*/  align; int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_video_context ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  TYPE_4__ video_splitter_t ;
struct TYPE_22__ {char* psz_module; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_5__ video_splitter_output_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct vlc_vidsplit_part {int width; int height; int /*<<< orphan*/  lock; TYPE_1__* display; int /*<<< orphan*/ * window; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/ * VLC_OBJECT (TYPE_1__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * module_need (TYPE_4__*,char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * video_splitter_CreateWindow (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,struct vlc_vidsplit_part*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 void* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* vlc_object_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vidsplit_Close (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_vidsplit_Control ; 
 int /*<<< orphan*/  vlc_vidsplit_Display ; 
 int /*<<< orphan*/  vlc_vidsplit_Prepare ; 
 TYPE_1__* vout_display_New (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_SetSize (TYPE_1__*,int,int) ; 
 scalar_t__ vout_display_cfg_IsWindowed (TYPE_3__ const*) ; 
 int /*<<< orphan*/  vout_window_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_window_Disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_vidsplit_Open(vout_display_t *vd,
                             const vout_display_cfg_t *cfg,
                             video_format_t *fmtp, vlc_video_context *ctx)
{
    vlc_object_t *obj = VLC_OBJECT(vd);

    if (vout_display_cfg_IsWindowed(cfg))
        return VLC_EGENERIC;

    char *name = var_InheritString(obj, "video-splitter");
    if (name == NULL)
        return VLC_EGENERIC;

    vout_display_sys_t *sys = vlc_object_create(obj, sizeof (*sys));
    if (unlikely(sys == NULL)) {
        free(name);
        return VLC_ENOMEM;
    }
    vd->sys = sys;

    video_splitter_t *splitter = &sys->splitter;

    vlc_mutex_init(&sys->lock);
    video_format_Copy(&splitter->fmt, &vd->source);

    splitter->p_module = module_need(splitter, "video splitter", name, true);
    free(name);
    if (splitter->p_module == NULL) {
        video_format_Clean(&splitter->fmt);
        vlc_mutex_destroy(&sys->lock);
        vlc_object_delete(splitter);
        return VLC_EGENERIC;
    }

    sys->pictures = vlc_obj_malloc(obj, splitter->i_output
                                        * sizeof (*sys->pictures));
    sys->parts = vlc_obj_malloc(obj,
                                splitter->i_output * sizeof (*sys->parts));
    if (unlikely(sys->pictures == NULL || sys->parts == NULL)) {
        splitter->i_output = 0;
        vlc_vidsplit_Close(vd);
        return VLC_ENOMEM;
    }

    for (int i = 0; i < splitter->i_output; i++) {
        const video_splitter_output_t *output = &splitter->p_output[i];
        vout_display_cfg_t vdcfg = {
            .display = { 0, 0, { 1, 1 } },
            .align = { 0, 0 } /* TODO */,
            .is_display_filled = true,
            .zoom = { 1, 1 },
        };
        const char *modname = output->psz_module;
        struct vlc_vidsplit_part *part = &sys->parts[i];

        vlc_sem_init(&part->lock, 1);
        part->display = NULL;
        part->width = 1;
        part->height = 1;

        part->window = video_splitter_CreateWindow(obj, &vdcfg, &output->fmt,
                                                   part);
        if (part->window == NULL) {
            splitter->i_output = i;
            vlc_vidsplit_Close(vd);
            return VLC_EGENERIC;
        }

        vdcfg.window = part->window;
        vout_display_t *display = vout_display_New(obj, &output->fmt, ctx, &vdcfg,
                                                   modname, NULL);
        if (display == NULL) {
            vout_window_Disable(part->window);
            vout_window_Delete(part->window);
            vlc_sem_destroy(&part->lock);
            splitter->i_output = i;
            vlc_vidsplit_Close(vd);
            return VLC_EGENERIC;
        }

        vlc_sem_wait(&part->lock);
        part->display = display;
        vout_display_SetSize(display, part->width, part->height);
        vlc_sem_post(&part->lock);
    }

    vd->prepare = vlc_vidsplit_Prepare;
    vd->display = vlc_vidsplit_Display;
    vd->control = vlc_vidsplit_Control;
    vd->close = vlc_vidsplit_Close;
    (void) fmtp;
    return VLC_SUCCESS;
}