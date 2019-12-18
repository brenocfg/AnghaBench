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
 scalar_t__ IWbemPath_GetClassName (int /*<<< orphan*/ *,int*,char*) ; 
 scalar_t__ IWbemPath_GetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IWbemPath_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemPath_SetClassName (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ S_OK ; 
 int WBEMPATH_INFO_ANON_LOCAL_MACHINE ; 
 int WBEMPATH_INFO_CIM_COMPLIANT ; 
 int WBEMPATH_INFO_HAS_SUBSCOPES ; 
 int WBEMPATH_INFO_IS_CLASS_REF ; 
 int WBEMPATH_INFO_V2_COMPLIANT ; 
 scalar_t__ WBEM_E_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * create_path () ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ wine_dbgstr_longlong (int) ; 
 scalar_t__ wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_IWbemPath_SetClassName(void)
{
    static const WCHAR classW[] = {'c','l','a','s','s',0};
    static const WCHAR emptyW[] = {0};
    IWbemPath *path;
    WCHAR buf[16];
    ULONG len;
    ULONGLONG flags;
    HRESULT hr;

    if (!(path = create_path())) return;

    hr = IWbemPath_SetClassName( path, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    hr = IWbemPath_SetClassName( path, emptyW );
    ok( hr == S_OK, "got %08x\n", hr );

    hr = IWbemPath_SetClassName( path, classW );
    ok( hr == S_OK, "got %08x\n", hr );

    buf[0] = 0;
    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetClassName( path, &len, buf );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( !lstrcmpW( buf, classW ), "unexpected buffer contents %s\n", wine_dbgstr_w(buf) );

    flags = 0;
    hr = IWbemPath_GetInfo( path, 0, &flags );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( flags == (WBEMPATH_INFO_ANON_LOCAL_MACHINE | WBEMPATH_INFO_IS_CLASS_REF |
                  WBEMPATH_INFO_HAS_SUBSCOPES | WBEMPATH_INFO_V2_COMPLIANT |
                  WBEMPATH_INFO_CIM_COMPLIANT),
        "got %s\n", wine_dbgstr_longlong(flags) );

    IWbemPath_Release( path );
}