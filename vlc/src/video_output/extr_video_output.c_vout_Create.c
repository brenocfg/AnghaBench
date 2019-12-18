#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {TYPE_9__* p; } ;
typedef  TYPE_8__ vout_thread_t ;
struct TYPE_30__ {int /*<<< orphan*/ * window; } ;
struct TYPE_29__ {int /*<<< orphan*/  lock; } ;
struct TYPE_28__ {void* position; void* timeout; void* show; } ;
struct TYPE_26__ {int /*<<< orphan*/  mode; } ;
struct TYPE_25__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_27__ {TYPE_3__ crop; TYPE_2__ dar; } ;
struct TYPE_24__ {scalar_t__ i_chroma; } ;
struct TYPE_32__ {int dummy; int window_enabled; TYPE_7__ display_cfg; int /*<<< orphan*/  refs; int /*<<< orphan*/  render; int /*<<< orphan*/  window_lock; int /*<<< orphan*/ * splitter_name; int /*<<< orphan*/ * spu; int /*<<< orphan*/  display_lock; int /*<<< orphan*/ * display; TYPE_6__ filter; void* is_late_dropped; TYPE_5__ title; int /*<<< orphan*/  control; int /*<<< orphan*/  statistic; int /*<<< orphan*/  snapshot; TYPE_4__ source; TYPE_1__ original; } ;
typedef  TYPE_9__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  VOUT_CROP_NONE ; 
 int /*<<< orphan*/  VOUT_WINDOW_STATE_ABOVE ; 
 int /*<<< orphan*/  VOUT_WINDOW_STATE_BELOW ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ config_GetType (char*) ; 
 int /*<<< orphan*/ * spu_Create (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  spu_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Create (TYPE_8__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_Destroy (TYPE_8__*,char*) ; 
 void* var_InheritBool (TYPE_8__*,char*) ; 
 void* var_InheritInteger (TYPE_8__*,char*) ; 
 int /*<<< orphan*/ * var_InheritString (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  var_SetString (TYPE_8__*,char*,char*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_8__*) ; 
 TYPE_8__* vout_CreateCommon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_InitInterlacingSupport (TYPE_8__*) ; 
 int /*<<< orphan*/  vout_IntfInit (TYPE_8__*) ; 
 int /*<<< orphan*/  vout_chrono_Init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_control_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vout_display_window_New (TYPE_8__*) ; 
 int /*<<< orphan*/  vout_snapshot_New () ; 
 int /*<<< orphan*/  vout_statistic_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_window_SetState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vout_thread_t *vout_Create(vlc_object_t *object)
{
    vout_thread_t *vout = vout_CreateCommon(object);
    if (!vout)
        return NULL;
    vout_thread_sys_t *sys = vout->p;
    sys->dummy = false;

    /* Register the VLC variable and callbacks. On the one hand, the variables
     * must be ready early on because further initializations below depend on
     * some of them. On the other hand, the callbacks depend on said
     * initializations. In practice, this works because the object is not
     * visible and callbacks not triggerable before this function returns the
     * fully initialized object to its caller.
     */
    vout_IntfInit(vout);

    /* Get splitter name if present */
    sys->splitter_name = config_GetType("video-splitter") ?
        var_InheritString(vout, "video-splitter") : NULL;
    if (sys->splitter_name != NULL) {
        var_Create(vout, "window", VLC_VAR_STRING);
        var_SetString(vout, "window", "wdummy");
    }

    sys->original.i_chroma = 0;
    sys->source.dar.num = 0;
    sys->source.dar.den = 0;
    sys->source.crop.mode = VOUT_CROP_NONE;
    sys->snapshot = vout_snapshot_New();
    vout_statistic_Init(&sys->statistic);

    /* Initialize subpicture unit */
    sys->spu = var_InheritBool(vout, "spu") || var_InheritBool(vout, "osd") ?
               spu_Create(vout, vout) : NULL;

    vout_control_Init(&sys->control);

    sys->title.show     = var_InheritBool(vout, "video-title-show");
    sys->title.timeout  = var_InheritInteger(vout, "video-title-timeout");
    sys->title.position = var_InheritInteger(vout, "video-title-position");

    vout_InitInterlacingSupport(vout);

    sys->is_late_dropped = var_InheritBool(vout, "drop-late-frames");

    vlc_mutex_init(&sys->filter.lock);

    /* Display */
    sys->display = NULL;
    vlc_mutex_init(&sys->display_lock);

    /* Window */
    sys->display_cfg.window = vout_display_window_New(vout);
    if (sys->display_cfg.window == NULL) {
        if (sys->spu)
            spu_Destroy(sys->spu);
        vlc_object_delete(vout);
        return NULL;
    }

    if (sys->splitter_name != NULL)
        var_Destroy(vout, "window");
    sys->window_enabled = false;
    vlc_mutex_init(&sys->window_lock);

    /* Arbitrary initial time */
    vout_chrono_Init(&sys->render, 5, VLC_TICK_FROM_MS(10));

    /* */
    atomic_init(&sys->refs, 0);

    if (var_InheritBool(vout, "video-wallpaper"))
        vout_window_SetState(sys->display_cfg.window, VOUT_WINDOW_STATE_BELOW);
    else if (var_InheritBool(vout, "video-on-top"))
        vout_window_SetState(sys->display_cfg.window, VOUT_WINDOW_STATE_ABOVE);

    return vout;
}