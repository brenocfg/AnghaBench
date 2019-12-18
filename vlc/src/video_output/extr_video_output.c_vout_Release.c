#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* p; } ;
typedef  TYPE_3__ vout_thread_t ;
struct TYPE_8__ {int /*<<< orphan*/  window; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  original; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  statistic; int /*<<< orphan*/  display_lock; int /*<<< orphan*/  control; TYPE_2__ display_cfg; int /*<<< orphan*/  window_enabled; scalar_t__ dec_device; TYPE_1__ filter; int /*<<< orphan*/  window_lock; int /*<<< orphan*/  splitter_name; scalar_t__ dummy; int /*<<< orphan*/  refs; } ;
typedef  TYPE_4__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_fetch_sub_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_decoder_device_Release (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_control_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_window_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_snapshot_Destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_statistic_Clean (int /*<<< orphan*/ *) ; 

void vout_Release(vout_thread_t *vout)
{
    vout_thread_sys_t *sys = vout->p;

    if (atomic_fetch_sub_explicit(&sys->refs, 1, memory_order_release))
        return;

    if (sys->dummy)
    {
        vlc_object_delete(VLC_OBJECT(vout));
        return;
    }

    free(sys->splitter_name);

    /* Destroy the locks */
    vlc_mutex_destroy(&sys->window_lock);
    vlc_mutex_destroy(&sys->filter.lock);

    if (sys->dec_device)
        vlc_decoder_device_Release(sys->dec_device);

    assert(!sys->window_enabled);
    vout_display_window_Delete(sys->display_cfg.window);

    vout_control_Clean(&sys->control);
    vlc_mutex_destroy(&sys->display_lock);

    /* */
    vout_statistic_Clean(&sys->statistic);

    /* */
    vout_snapshot_Destroy(sys->snapshot);
    video_format_Clean(&sys->original);
    vlc_object_delete(VLC_OBJECT(vout));
}