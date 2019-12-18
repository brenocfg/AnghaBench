#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  inhibit; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  thread; scalar_t__ mask; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Inhibit ; 
 int /*<<< orphan*/  Run ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int OpenInhibit (vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *sys = ih->p_sys =
            vlc_obj_malloc(obj, sizeof(vlc_inhibit_sys_t));
    if (unlikely(ih->p_sys == NULL))
        return VLC_ENOMEM;

    vlc_mutex_init(&sys->mutex);
    vlc_cond_init(&sys->cond);
    sys->mask = 0;

    /* SetThreadExecutionState always needs to be called from the same thread */
    if (vlc_clone(&sys->thread, Run, ih, VLC_THREAD_PRIORITY_LOW))
    {
        vlc_cond_destroy(&sys->cond);
        vlc_mutex_destroy(&sys->mutex);
        return VLC_EGENERIC;
    }

    ih->inhibit = Inhibit;
    return VLC_SUCCESS;
}