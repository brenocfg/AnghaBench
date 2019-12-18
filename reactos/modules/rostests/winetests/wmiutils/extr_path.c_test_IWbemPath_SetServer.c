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
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IWbemPath ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IWbemPath_GetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ IWbemPath_GetServer (int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  IWbemPath_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemPath_SetServer (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ S_OK ; 
 int WBEMPATH_INFO_ANON_LOCAL_MACHINE ; 
 int WBEMPATH_INFO_CIM_COMPLIANT ; 
 int WBEMPATH_INFO_HAS_MACHINE_NAME ; 
 int WBEMPATH_INFO_PATH_HAD_SERVER ; 
 int WBEMPATH_INFO_SERVER_NAMESPACE_ONLY ; 
 int WBEMPATH_INFO_V1_COMPLIANT ; 
 int WBEMPATH_INFO_V2_COMPLIANT ; 
 scalar_t__ WBEM_E_NOT_AVAILABLE ; 
 int /*<<< orphan*/ * create_path () ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_longlong (int) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_IWbemPath_SetServer(void)
{
    static const WCHAR serverW[] = {'s','e','r','v','e','r',0};
    static const WCHAR emptyW[] = {0};
    IWbemPath *path;
    WCHAR buf[16];
    ULONG len;
    ULONGLONG flags;
    HRESULT hr;

    if (!(path = create_path())) return;

    hr = IWbemPath_SetServer( path, NULL );
    ok( hr == S_OK, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetServer( path, &len, buf );
    ok( hr == WBEM_E_NOT_AVAILABLE, "got %08x\n", hr );

    hr = IWbemPath_SetServer( path, emptyW );
    ok( hr == S_OK, "got %08x\n", hr );

    hr = IWbemPath_SetServer( path, serverW );
    ok( hr == S_OK, "got %08x\n", hr );

    buf[0] = 0;
    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetServer( path, &len, buf );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( !lstrcmpW( buf, serverW ), "unexpected buffer contents %s\n", wine_dbgstr_w(buf) );

    flags = 0;
    hr = IWbemPath_GetInfo( path, 0, &flags );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( flags == (WBEMPATH_INFO_HAS_MACHINE_NAME | WBEMPATH_INFO_V1_COMPLIANT |
                  WBEMPATH_INFO_V2_COMPLIANT | WBEMPATH_INFO_CIM_COMPLIANT |
                  WBEMPATH_INFO_SERVER_NAMESPACE_ONLY | WBEMPATH_INFO_PATH_HAD_SERVER),
        "got %s\n", wine_dbgstr_longlong(flags) );

    hr = IWbemPath_SetServer( path, NULL );
    ok( hr == S_OK, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetServer( path, &len, buf );
    ok( hr == WBEM_E_NOT_AVAILABLE, "got %08x\n", hr );

    flags = 0;
    hr = IWbemPath_GetInfo( path, 0, &flags );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( flags == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_SERVER_NAMESPACE_ONLY),
        "got %s\n", wine_dbgstr_longlong(flags) );

    IWbemPath_Release( path );
}