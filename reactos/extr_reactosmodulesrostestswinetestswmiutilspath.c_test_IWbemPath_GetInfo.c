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
typedef  int ULONGLONG ;
typedef  int /*<<< orphan*/  IWbemPath ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IWbemPath_GetInfo (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IWbemPath_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemPath_SetText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  WBEMPATH_CREATE_ACCEPT_ALL ; 
 int WBEMPATH_INFO_ANON_LOCAL_MACHINE ; 
 int WBEMPATH_INFO_CIM_COMPLIANT ; 
 int WBEMPATH_INFO_HAS_SUBSCOPES ; 
 int WBEMPATH_INFO_IS_CLASS_REF ; 
 int WBEMPATH_INFO_IS_INST_REF ; 
 int WBEMPATH_INFO_PATH_HAD_SERVER ; 
 int WBEMPATH_INFO_SERVER_NAMESPACE_ONLY ; 
 int WBEMPATH_INFO_V2_COMPLIANT ; 
 scalar_t__ WBEM_E_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * create_path () ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  path1 ; 
 int /*<<< orphan*/  path12 ; 
 int /*<<< orphan*/  path17 ; 
 scalar_t__ wine_dbgstr_longlong (int) ; 

__attribute__((used)) static void test_IWbemPath_GetInfo(void)
{
    IWbemPath *path;
    HRESULT hr;
    ULONGLONG resp;

    if (!(path = create_path())) return;

    hr = IWbemPath_GetInfo( path, 0, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    hr = IWbemPath_GetInfo( path, 1, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    resp = 0xdeadbeef;
    hr = IWbemPath_GetInfo( path, 0, &resp );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( resp == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_SERVER_NAMESPACE_ONLY),
        "got %s\n", wine_dbgstr_longlong(resp) );

    hr = IWbemPath_SetText( path, WBEMPATH_CREATE_ACCEPT_ALL, path17 );
    ok( hr == S_OK, "got %08x\n", hr );

    hr = IWbemPath_GetInfo( path, 0, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    hr = IWbemPath_GetInfo( path, 1, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    resp = 0xdeadbeef;
    hr = IWbemPath_GetInfo( path, 0, &resp );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( resp == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_IS_INST_REF |
                 WBEMPATH_INFO_HAS_SUBSCOPES | WBEMPATH_INFO_V2_COMPLIANT |
                 WBEMPATH_INFO_CIM_COMPLIANT | WBEMPATH_INFO_PATH_HAD_SERVER),
        "got %s\n", wine_dbgstr_longlong(resp) );

    IWbemPath_Release( path );
    if (!(path = create_path())) return;

    hr = IWbemPath_SetText( path, WBEMPATH_CREATE_ACCEPT_ALL, path12 );
    ok( hr == S_OK, "got %08x\n", hr );

    resp = 0xdeadbeef;
    hr = IWbemPath_GetInfo( path, 0, &resp );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( resp == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_IS_CLASS_REF |
                 WBEMPATH_INFO_HAS_SUBSCOPES | WBEMPATH_INFO_V2_COMPLIANT |
                 WBEMPATH_INFO_CIM_COMPLIANT),
        "got %s\n", wine_dbgstr_longlong(resp) );

    hr = IWbemPath_SetText( path, WBEMPATH_CREATE_ACCEPT_ALL, path1 );
    ok( hr == S_OK, "got %08x\n", hr );

    resp = 0xdeadbeef;
    hr = IWbemPath_GetInfo( path, 0, &resp );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( resp == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_SERVER_NAMESPACE_ONLY),
        "got %s\n", wine_dbgstr_longlong(resp) );

    IWbemPath_Release( path );
}