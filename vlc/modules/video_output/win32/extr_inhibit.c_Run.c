#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ vlc_inhibit_t ;
struct TYPE_5__ {unsigned int mask; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_2__ vlc_inhibit_sys_t ;
typedef  int EXECUTION_STATE ;

/* Variables and functions */
 int ES_CONTINUOUS ; 
 int ES_DISPLAY_REQUIRED ; 
 int ES_SYSTEM_REQUIRED ; 
 int /*<<< orphan*/  RestoreStateOnCancel ; 
 int SetThreadExecutionState (int) ; 
 unsigned int VLC_INHIBIT_DISPLAY ; 
 int /*<<< orphan*/  mutex_cleanup_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* Run(void* obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t*)obj;
    vlc_inhibit_sys_t *sys = ih->p_sys;
    EXECUTION_STATE prev_state = ES_CONTINUOUS;

    for  (unsigned int mask = 0;;)
    {
        vlc_mutex_lock(&sys->mutex);
        mutex_cleanup_push(&sys->mutex);
        vlc_cleanup_push(RestoreStateOnCancel, ih);
        while (mask == sys->mask)
            vlc_cond_wait(&sys->cond, &sys->mutex);
        mask = sys->mask;
        vlc_mutex_unlock(&sys->mutex);
        vlc_cleanup_pop();
        vlc_cleanup_pop();

        bool suspend = (mask & VLC_INHIBIT_DISPLAY) != 0;
        if (suspend)
            /* Prevent monitor from powering off */
            prev_state = SetThreadExecutionState( ES_DISPLAY_REQUIRED |
                                                  ES_SYSTEM_REQUIRED |
                                                  ES_CONTINUOUS );
        else
            SetThreadExecutionState( prev_state );
    }
    vlc_assert_unreachable();
}