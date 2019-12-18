#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  window; } ;
struct TYPE_7__ {int window_enabled; int /*<<< orphan*/  window_lock; TYPE_1__ display_cfg; int /*<<< orphan*/ * dec_device; } ;
typedef  TYPE_3__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_decoder_device_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_window_Disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vout_DisableWindow(vout_thread_t *vout)
{
    vout_thread_sys_t *sys = vout->p;
    vlc_mutex_lock(&sys->window_lock);
    if (sys->dec_device)
    {
        vlc_decoder_device_Release(sys->dec_device);
        sys->dec_device = NULL;
    }
    if (sys->window_enabled) {
        vout_window_Disable(sys->display_cfg.window);
        sys->window_enabled = false;
    }
    vlc_mutex_unlock(&sys->window_lock);
}