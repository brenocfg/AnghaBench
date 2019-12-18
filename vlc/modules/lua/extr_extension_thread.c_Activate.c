#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct extension_sys_t {int b_activated; int b_thread_running; int b_exiting; int /*<<< orphan*/  thread; int /*<<< orphan*/  command_lock; int /*<<< orphan*/  wait; TYPE_3__* command; } ;
struct command_t {int dummy; } ;
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_5__ {int /*<<< orphan*/  psz_title; struct extension_sys_t* p_sys; } ;
typedef  TYPE_1__ extension_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACTIVATE ; 
 int /*<<< orphan*/  Run ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int Activate( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    assert( p_ext != NULL );

    struct extension_sys_t *p_sys = p_ext->p_sys;
    assert( p_sys != NULL );

    vlc_mutex_lock( &p_sys->command_lock );
    if ( p_sys->b_activated == false )
    {
        /* Prepare first command */
        assert(p_sys->command == NULL);
        p_sys->command = calloc( 1, sizeof( struct command_t ) );
        if( !p_sys->command )
        {
            vlc_mutex_unlock( &p_sys->command_lock );
            return VLC_ENOMEM;
        }
        p_sys->command->i_command = CMD_ACTIVATE; /* No params */
        if (p_sys->b_thread_running == true)
        {
            msg_Dbg( p_mgr, "Reactivating extension %s", p_ext->psz_title);
            vlc_cond_signal( &p_sys->wait );
        }
    }
    vlc_mutex_unlock( &p_sys->command_lock );

    if (p_sys->b_thread_running == true)
        return VLC_SUCCESS;

    msg_Dbg( p_mgr, "Activating extension '%s'", p_ext->psz_title );
    /* Start thread */
    p_sys->b_exiting = false;
    p_sys->b_thread_running = true;

    if( vlc_clone( &p_sys->thread, Run, p_ext, VLC_THREAD_PRIORITY_LOW )
        != VLC_SUCCESS )
    {
        p_sys->b_exiting = true;
        p_sys->b_thread_running = false;
        return VLC_ENOMEM;
    }

    return VLC_SUCCESS;
}