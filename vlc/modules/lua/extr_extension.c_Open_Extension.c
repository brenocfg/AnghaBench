#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_sys; int /*<<< orphan*/  pf_control; } ;
typedef  TYPE_1__ extensions_manager_t ;

/* Variables and functions */
 int /*<<< orphan*/  Control ; 
 scalar_t__ ScanExtensions (TYPE_1__*) ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_VAR_ADDRESS ; 
 scalar_t__ lua_Disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_extension_dialog_callback ; 

int Open_Extension( vlc_object_t *p_this )
{
    if( lua_Disabled( p_this ) )
        return VLC_EGENERIC;

    msg_Dbg( p_this, "Opening Lua Extension module" );

    extensions_manager_t *p_mgr = ( extensions_manager_t* ) p_this;

    p_mgr->pf_control = Control;

    p_mgr->p_sys = NULL;
    vlc_mutex_init( &p_mgr->lock );

    /* Scan available Lua Extensions */
    if( ScanExtensions( p_mgr ) != VLC_SUCCESS )
    {
        msg_Err( p_mgr, "Can't load extensions modules" );
        return VLC_EGENERIC;
    }

    // Create the dialog-event variable
    var_Create( p_this, "dialog-event", VLC_VAR_ADDRESS );
    var_AddCallback( p_this, "dialog-event",
                     vlclua_extension_dialog_callback, NULL );

    return VLC_SUCCESS;
}