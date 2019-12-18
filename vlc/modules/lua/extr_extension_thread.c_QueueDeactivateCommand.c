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
struct command_t {struct command_t* next; int /*<<< orphan*/  i_command; } ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_4__ {int /*<<< orphan*/  wait; struct command_t* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DEACTIVATE ; 
 int /*<<< orphan*/  FreeCommands (struct command_t*) ; 
 struct command_t* calloc (int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 

bool QueueDeactivateCommand( extension_t *p_ext )
{
    struct command_t *cmd = calloc( 1, sizeof( struct command_t ) );
    if( unlikely( cmd == NULL ) )
        return false;
    /* Free the list of commands */
    if( p_ext->p_sys->command )
        FreeCommands( p_ext->p_sys->command->next );

    /* Push command */

    cmd->i_command = CMD_DEACTIVATE;
    if( p_ext->p_sys->command )
        p_ext->p_sys->command->next = cmd;
    else
        p_ext->p_sys->command = cmd;

    vlc_cond_signal( &p_ext->p_sys->wait );
    return true;
}