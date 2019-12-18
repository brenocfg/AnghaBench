#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* p_address; } ;
typedef  TYPE_2__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  extension_widget_t ;
typedef  int /*<<< orphan*/  extension_t ;
struct TYPE_8__ {int event; int /*<<< orphan*/ * p_data; TYPE_1__* p_dlg; } ;
typedef  TYPE_3__ extension_dialog_command_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CLICK ; 
 int /*<<< orphan*/  CMD_CLOSE ; 
#define  EXTENSION_EVENT_CLICK 129 
#define  EXTENSION_EVENT_CLOSE 128 
 int /*<<< orphan*/  PushCommandUnique (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int vlclua_extension_dialog_callback( vlc_object_t *p_this,
                                             char const *psz_var,
                                             vlc_value_t oldval,
                                             vlc_value_t newval,
                                             void *p_data )
{
    /* psz_var == "dialog-event" */
    ( void ) psz_var;
    ( void ) oldval;
    ( void ) p_data;

    extension_dialog_command_t *command = newval.p_address;
    assert( command != NULL );
    assert( command->p_dlg != NULL);

    extension_t *p_ext = command->p_dlg->p_sys;
    assert( p_ext != NULL );

    extension_widget_t *p_widget = command->p_data;

    switch( command->event )
    {
        case EXTENSION_EVENT_CLICK:
            assert( p_widget != NULL );
            PushCommandUnique( p_ext, CMD_CLICK, p_widget );
            break;
        case EXTENSION_EVENT_CLOSE:
            PushCommandUnique( p_ext, CMD_CLOSE );
            break;
        default:
            msg_Dbg( p_this, "Received unknown UI event %d, discarded",
                     command->event );
            break;
    }

    return VLC_SUCCESS;
}