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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ControlService (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int SERVICE_PAUSE_CONTINUE ; 
 int SERVICE_START ; 
 int SERVICE_STOP ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  map_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT control_service( const WCHAR *name, DWORD control, VARIANT *retval )
{
    SC_HANDLE manager, service = NULL;
    SERVICE_STATUS status;
    UINT error = 0;

    if (!(manager = OpenSCManagerW( NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE )))
    {
        error = map_error( GetLastError() );
        goto done;
    }
    if (!(service = OpenServiceW( manager, name, SERVICE_STOP|SERVICE_START|SERVICE_PAUSE_CONTINUE )))
    {
        error = map_error( GetLastError() );
        goto done;
    }
    if (!ControlService( service, control, &status )) error = map_error( GetLastError() );
    CloseServiceHandle( service );

done:
    set_variant( VT_UI4, error, NULL, retval );
    if (manager) CloseServiceHandle( manager );
    return S_OK;
}