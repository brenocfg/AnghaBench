#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_14__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_12__ {scalar_t__ psz_service; } ;
typedef  TYPE_3__ SERVICE_TABLE_ENTRY ;
typedef  int /*<<< orphan*/ * LPSERVICE_MAIN_FUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  NTServiceInstall (TYPE_2__*) ; 
 int /*<<< orphan*/  NTServiceUninstall (TYPE_2__*) ; 
 int /*<<< orphan*/  ServiceDispatch ; 
 scalar_t__ StartServiceCtrlDispatcher (TYPE_3__*) ; 
 scalar_t__ TEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLCSERVICENAME ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  libvlc_Quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 TYPE_2__* p_global_intf ; 
 scalar_t__ strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (TYPE_2__*,char*) ; 
 scalar_t__ var_InheritString (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_2__*) ; 

__attribute__((used)) static void *Run( void *data )
{
    intf_thread_t *p_intf = data;
    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { (WCHAR*) TEXT(VLCSERVICENAME), (LPSERVICE_MAIN_FUNCTION) &ServiceDispatch },
        { NULL, NULL }
    };

    p_global_intf = p_intf;
    p_intf->p_sys->psz_service = var_InheritString( p_intf, "ntservice-name" );
    p_intf->p_sys->psz_service = p_intf->p_sys->psz_service ?
        p_intf->p_sys->psz_service : strdup(VLCSERVICENAME);

    if( var_InheritBool( p_intf, "ntservice-install" ) )
    {
        NTServiceInstall( p_intf );
        return NULL;
    }

    if( var_InheritBool( p_intf, "ntservice-uninstall" ) )
    {
        NTServiceUninstall( p_intf );
        return NULL;
    }

    if( StartServiceCtrlDispatcher( dispatchTable ) == 0 )
    {
        msg_Err( p_intf, "StartServiceCtrlDispatcher failed" ); /* str review */
    }

    free( p_intf->p_sys->psz_service );

    /* Make sure we exit (In case other interfaces have been spawned) */
    libvlc_Quit( vlc_object_instance(p_intf) );
    return NULL;
}