#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct command_t {int i_command; struct command_t** data; struct command_t* next; } ;

/* Variables and functions */
#define  CMD_ACTIVATE 132 
#define  CMD_CLICK 131 
#define  CMD_DEACTIVATE 130 
#define  CMD_PLAYING_CHANGED 129 
#define  CMD_TRIGGERMENU 128 
 int /*<<< orphan*/  free (struct command_t*) ; 

__attribute__((used)) static void FreeCommands( struct command_t *command )
{
    if( !command ) return;
    struct command_t *next = command->next;
    switch( command->i_command )
    {
        case CMD_ACTIVATE:
        case CMD_DEACTIVATE:
        case CMD_CLICK: // Arg1 must not be freed
            break;

        case CMD_TRIGGERMENU:
        case CMD_PLAYING_CHANGED:
            free( command->data[0] ); // Arg1 is int*, to free
            break;

        default:
            break;
    }
    free( command );
    FreeCommands( next );
}