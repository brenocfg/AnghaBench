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
typedef  scalar_t__ vlc_action_id_t ;
struct TYPE_7__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lirc_code2char (int /*<<< orphan*/ ,char*,char**) ; 
 scalar_t__ lirc_nextcode (char**) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  var_SetInteger (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ vlc_actions_get_id (char*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_2__*) ; 

__attribute__((used)) static void Process( intf_thread_t *p_intf )
{
    for( ;; )
    {
        char *code, *c;
        if( lirc_nextcode( &code ) )
            return;

        if( code == NULL )
            return;

        while( (lirc_code2char( p_intf->p_sys->config, code, &c ) == 0)
                && (c != NULL) )
        {
            if( !strncmp( "key-", c, 4 ) )
            {
                vlc_action_id_t i_key = vlc_actions_get_id( c );
                if( i_key )
                    var_SetInteger( vlc_object_instance(p_intf), "key-action", i_key );
                else
                    msg_Err( p_intf, "Unknown hotkey '%s'", c );
            }
            else
            {
                msg_Err( p_intf, "this doesn't appear to be a valid keycombo "
                                 "lirc sent us. Please look at the "
                                 "doc/lirc/example.lirc file in VLC" );
                break;
            }
        }
        free( code );
    }
}