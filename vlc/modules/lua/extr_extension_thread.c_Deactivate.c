#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_7__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_6__ {int /*<<< orphan*/  command_lock; int /*<<< orphan*/ * p_progress_id; scalar_t__ b_exiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  KillExtension (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int QueueDeactivateCommand (TYPE_2__*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vlc_dialog_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int Deactivate( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    vlc_mutex_lock( &p_ext->p_sys->command_lock );

    if( p_ext->p_sys->b_exiting )
    {
        vlc_mutex_unlock( &p_ext->p_sys->command_lock );
        return VLC_EGENERIC;
    }

    if( p_ext->p_sys->p_progress_id != NULL )
    {
        // Extension is stuck, kill it now
        vlc_dialog_release( p_mgr, p_ext->p_sys->p_progress_id );
        p_ext->p_sys->p_progress_id = NULL;
        KillExtension( p_mgr, p_ext );
        vlc_mutex_unlock( &p_ext->p_sys->command_lock );
        return VLC_SUCCESS;
    }

    bool b_success = QueueDeactivateCommand( p_ext );
    vlc_mutex_unlock( &p_ext->p_sys->command_lock );

    return b_success ? VLC_SUCCESS : VLC_ENOMEM;
}