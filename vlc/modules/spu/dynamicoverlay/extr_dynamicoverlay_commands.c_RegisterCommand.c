#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {size_t i_commands; TYPE_3__** pp_commands; } ;
typedef  TYPE_2__ filter_sys_t ;
struct TYPE_10__ {size_t psz_command; int /*<<< orphan*/  pf_unparse; int /*<<< orphan*/  pf_execute; int /*<<< orphan*/  pf_parser; int /*<<< orphan*/  b_atomic; } ;
typedef  TYPE_3__ commanddesc_t ;
struct TYPE_11__ {int /*<<< orphan*/  pf_unparse; int /*<<< orphan*/  pf_execute; int /*<<< orphan*/  pf_parser; int /*<<< orphan*/  b_atomic; int /*<<< orphan*/  psz_command; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 scalar_t__ calloc (size_t,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,size_t) ; 
 TYPE_4__* p_commands ; 
 size_t strdup (int /*<<< orphan*/ ) ; 

void RegisterCommand( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    p_sys->i_commands = ARRAY_SIZE(p_commands);
    p_sys->pp_commands = (commanddesc_t **) calloc( p_sys->i_commands, sizeof(commanddesc_t*) );
    if( !p_sys->pp_commands ) return;
    for( size_t i_index = 0; i_index < p_sys->i_commands; i_index ++ )
    {
        p_sys->pp_commands[i_index] = (commanddesc_t *) malloc( sizeof(commanddesc_t) );
        if( !p_sys->pp_commands[i_index] ) return;
        p_sys->pp_commands[i_index]->psz_command = strdup( p_commands[i_index].psz_command );
        p_sys->pp_commands[i_index]->b_atomic = p_commands[i_index].b_atomic;
        p_sys->pp_commands[i_index]->pf_parser = p_commands[i_index].pf_parser;
        p_sys->pp_commands[i_index]->pf_execute = p_commands[i_index].pf_execute;
        p_sys->pp_commands[i_index]->pf_unparse = p_commands[i_index].pf_unparse;
    }

    msg_Dbg( p_filter, "%zu commands are available", p_sys->i_commands );
    for( size_t i_index = 0; i_index < p_sys->i_commands; i_index++ )
        msg_Dbg( p_filter, "    %s", p_sys->pp_commands[i_index]->psz_command );
}