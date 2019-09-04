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
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ENUMERATE_SERVICE ; 
 int /*<<< orphan*/  SERVICE_START ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StartServiceW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  map_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_variant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT start_service( const WCHAR *name, VARIANT *retval )
{
    SC_HANDLE manager, service = NULL;
    UINT error = 0;

    if (!(manager = OpenSCManagerW( NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE )))
    {
        error = map_error( GetLastError() );
        goto done;
    }
    if (!(service = OpenServiceW( manager, name, SERVICE_START )))
    {
        error = map_error( GetLastError() );
        goto done;
    }
    if (!StartServiceW( service, 0, NULL )) error = map_error( GetLastError() );
    CloseServiceHandle( service );

done:
    set_variant( VT_UI4, error, NULL, retval );
    if (manager) CloseServiceHandle( manager );
    return S_OK;
}