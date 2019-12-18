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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_4__ {int /*<<< orphan*/  command_lock; int /*<<< orphan*/  timer; int /*<<< orphan*/ * p_progress_id; int /*<<< orphan*/  p_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TIMER_FIRE_ONCE ; 
 int /*<<< orphan*/  WATCH_TIMER_PERIOD ; 
 int /*<<< orphan*/  vlc_dialog_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_schedule (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* vlclua_extension_get (int /*<<< orphan*/ *) ; 

int vlclua_extension_keep_alive( lua_State *L )
{
    extension_t *p_ext = vlclua_extension_get( L );

    vlc_mutex_lock( &p_ext->p_sys->command_lock );
    if( p_ext->p_sys->p_progress_id != NULL )
    {
        vlc_dialog_release( p_ext->p_sys->p_mgr, p_ext->p_sys->p_progress_id );
        p_ext->p_sys->p_progress_id = NULL;
    }
    vlc_timer_schedule( p_ext->p_sys->timer, false, WATCH_TIMER_PERIOD,
                        VLC_TIMER_FIRE_ONCE );
    vlc_mutex_unlock( &p_ext->p_sys->command_lock );

    return 1;
}