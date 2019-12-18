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
struct command_t {scalar_t__ i_command; struct command_t* next; } ;
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_5__ {TYPE_1__* p_sys; int /*<<< orphan*/  psz_title; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_4__ {int /*<<< orphan*/  command_lock; int /*<<< orphan*/  timer; int /*<<< orphan*/ * p_progress_id; struct command_t* command; int /*<<< orphan*/ * p_mgr; } ;

/* Variables and functions */
 scalar_t__ CMD_DEACTIVATE ; 
 int /*<<< orphan*/  KillExtension (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  VLC_TIMER_FIRE_ONCE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * vlc_dialog_display_progress (int /*<<< orphan*/ *,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_dialog_is_cancelled (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_timer_schedule (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WatchTimerCallback( void *data )
{
    extension_t *p_ext = data;
    extensions_manager_t *p_mgr = p_ext->p_sys->p_mgr;

    vlc_mutex_lock( &p_ext->p_sys->command_lock );

    for( struct command_t *cmd = p_ext->p_sys->command;
         cmd != NULL;
         cmd = cmd->next )
        if( cmd->i_command == CMD_DEACTIVATE )
        {   /* We have a pending Deactivate command... */
            if( p_ext->p_sys->p_progress_id != NULL )
            {
                vlc_dialog_release( p_mgr, p_ext->p_sys->p_progress_id );
                p_ext->p_sys->p_progress_id = NULL;
            }
            KillExtension( p_mgr, p_ext );
            vlc_mutex_unlock( &p_ext->p_sys->command_lock );
            return;
        }

    if( p_ext->p_sys->p_progress_id == NULL )
    {
        p_ext->p_sys->p_progress_id =
            vlc_dialog_display_progress( p_mgr, true, 0.0,
                                         _( "Yes" ),
                                         _( "Extension not responding!" ),
                                         _( "Extension '%s' does not respond.\n"
                                         "Do you want to kill it now? " ),
                                         p_ext->psz_title );
        if( p_ext->p_sys->p_progress_id == NULL )
        {
            KillExtension( p_mgr, p_ext );
            vlc_mutex_unlock( &p_ext->p_sys->command_lock );
            return;
        }
        vlc_timer_schedule( p_ext->p_sys->timer, false, VLC_TICK_FROM_MS(100),
                            VLC_TIMER_FIRE_ONCE );
    }
    else
    {
        if( vlc_dialog_is_cancelled( p_mgr, p_ext->p_sys->p_progress_id ) )
        {
            vlc_dialog_release( p_mgr, p_ext->p_sys->p_progress_id );
            p_ext->p_sys->p_progress_id = NULL;
            KillExtension( p_mgr, p_ext );
            vlc_mutex_unlock( &p_ext->p_sys->command_lock );
            return;
        }
        vlc_timer_schedule( p_ext->p_sys->timer, false, VLC_TICK_FROM_MS(100),
                            VLC_TIMER_FIRE_ONCE );
    }
    vlc_mutex_unlock( &p_ext->p_sys->command_lock );
}