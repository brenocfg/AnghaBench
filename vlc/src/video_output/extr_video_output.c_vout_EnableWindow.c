#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  is_decorated; int /*<<< orphan*/  is_fullscreen; } ;
typedef  TYPE_1__ vout_window_cfg_t ;
struct TYPE_16__ {TYPE_3__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_14__ {int /*<<< orphan*/  window; } ;
struct TYPE_17__ {int window_enabled; int /*<<< orphan*/  window_lock; int /*<<< orphan*/ * dec_device; TYPE_13__ display_cfg; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_3__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
typedef  int /*<<< orphan*/  video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  VoutGetDisplayCfg (TYPE_2__*,int /*<<< orphan*/  const*,TYPE_13__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_GetBool (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_InheritBool (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  var_InheritInteger (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * vlc_decoder_device_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_decoder_device_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_SizeWindow (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_UpdateWindowSizeLocked (TYPE_2__*) ; 
 scalar_t__ vout_window_Enable (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int vout_EnableWindow(vout_thread_t *vout, const video_format_t *original,
                             vlc_decoder_device **pp_dec_device)
{
    vout_thread_sys_t *sys = vout->p;

    assert(!sys->dummy);
    assert(vout != NULL);

    vlc_mutex_lock(&sys->window_lock);
    if (!sys->window_enabled) {
        vout_window_cfg_t wcfg = {
            .is_fullscreen = var_GetBool(vout, "fullscreen"),
            .is_decorated = var_InheritBool(vout, "video-deco"),
        // TODO: take pixel A/R, crop and zoom into account
#if defined(__APPLE__) || defined(_WIN32)
            .x = var_InheritInteger(vout, "video-x"),
            .y = var_InheritInteger(vout, "video-y"),
#endif
        };

        VoutGetDisplayCfg(vout, original, &sys->display_cfg);
        vout_SizeWindow(vout, original, &wcfg.width, &wcfg.height);

        if (vout_window_Enable(sys->display_cfg.window, &wcfg)) {
            vlc_mutex_unlock(&sys->window_lock);
            msg_Err(vout, "failed to enable window");
            return -1;
        }
        sys->window_enabled = true;
    } else
        vout_UpdateWindowSizeLocked(vout);

    if (pp_dec_device)
    {
        if (sys->dec_device == NULL)
            sys->dec_device = vlc_decoder_device_Create(sys->display_cfg.window);
        *pp_dec_device = sys->dec_device ? vlc_decoder_device_Hold( sys->dec_device ) : NULL;
    }
    vlc_mutex_unlock(&sys->window_lock);
    return 0;
}