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
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  psz_service; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DELETE ; 
 int /*<<< orphan*/  DeleteService (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 

__attribute__((used)) static int NTServiceUninstall( intf_thread_t *p_intf )
{
    intf_sys_t *p_sys  = p_intf->p_sys;

    SC_HANDLE handle = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
    if( handle == NULL )
    {
        msg_Err( p_intf,
                 "could not connect to Services Control Manager database" );
        return VLC_EGENERIC;
    }

    /* First, open a handle to the service */
    SC_HANDLE service = OpenServiceA( handle, p_sys->psz_service, DELETE );
    if( service == NULL )
    {
        msg_Err( p_intf, "could not open service" );
        CloseServiceHandle( handle );
        return VLC_EGENERIC;
    }

    /* Remove the service */
    if( !DeleteService( service ) )
    {
        msg_Err( p_intf, "could not delete service \"%s\"",
                 p_sys->psz_service );
    }
    else
    {
        msg_Dbg( p_intf, "service deleted successfuly" );
    }

    CloseServiceHandle( service );
    CloseServiceHandle( handle );

    return VLC_SUCCESS;
}