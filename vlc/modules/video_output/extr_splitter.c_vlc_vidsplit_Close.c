#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_9__ {int i_output; int /*<<< orphan*/  fmt; int /*<<< orphan*/  p_module; } ;
struct TYPE_8__ {TYPE_5__ splitter; int /*<<< orphan*/  lock; struct vlc_vidsplit_part* parts; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct vlc_vidsplit_part {int /*<<< orphan*/  lock; int /*<<< orphan*/  window; TYPE_1__* display; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_unneed (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_Delete (TYPE_1__*) ; 
 int /*<<< orphan*/  vout_window_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_window_Disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_vidsplit_Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    int n = sys->splitter.i_output;

    for (int i = 0; i < n; i++) {
        struct vlc_vidsplit_part *part = &sys->parts[i];
        vout_display_t *display;

        vlc_sem_wait(&part->lock);
        display = part->display;
        part->display = NULL;
        vlc_sem_post(&part->lock);

        if (display != NULL)
            vout_display_Delete(display);

        vout_window_Disable(part->window);
        vout_window_Delete(part->window);
        vlc_sem_destroy(&part->lock);
    }

    module_unneed(&sys->splitter, sys->splitter.p_module);
    video_format_Clean(&sys->splitter.fmt);
    vlc_mutex_destroy(&sys->lock);
    vlc_object_delete(&sys->splitter);
}