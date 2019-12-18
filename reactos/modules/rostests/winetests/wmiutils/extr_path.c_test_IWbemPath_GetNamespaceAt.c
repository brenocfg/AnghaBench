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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IWbemPath ;
typedef  int HRESULT ;

/* Variables and functions */
 int IWbemPath_GetNamespaceAt (int /*<<< orphan*/ *,int,int*,char*) ; 
 int /*<<< orphan*/  IWbemPath_Release (int /*<<< orphan*/ *) ; 
 int IWbemPath_SetText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int /*<<< orphan*/  WBEMPATH_CREATE_ACCEPT_ALL ; 
 int WBEM_E_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * create_path () ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  path17 ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_IWbemPath_GetNamespaceAt(void)
{
    static const WCHAR rootW[] = {'r','o','o','t',0};
    static const WCHAR cimv2W[] = {'c','i','m','v','2',0};
    IWbemPath *path;
    HRESULT hr;
    WCHAR buf[32];
    ULONG len;

    if (!(path = create_path())) return;

    hr = IWbemPath_GetNamespaceAt( path, 0, NULL, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    len = 0;
    hr = IWbemPath_GetNamespaceAt( path, 0, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetNamespaceAt( path, 0, &len, buf );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetNamespaceAt( path, 0, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );
    ok( len == sizeof(buf) / sizeof(buf[0]), "unexpected length %u\n", len );

    hr = IWbemPath_SetText( path, WBEMPATH_CREATE_ACCEPT_ALL, path17 );
    ok( hr == S_OK, "got %08x\n", hr );

    len = 0;
    hr = IWbemPath_GetNamespaceAt( path, 2, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetNamespaceAt( path, 0, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );
    ok( len == sizeof(buf) / sizeof(buf[0]), "unexpected length %u\n", len );

    buf[0] = 0;
    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetNamespaceAt( path, 0, &len, buf );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( !lstrcmpW( buf, rootW ), "unexpected buffer contents %s\n", wine_dbgstr_w(buf) );
    ok( len == lstrlenW( rootW ) + 1, "unexpected length %u\n", len );

    buf[0] = 0;
    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetNamespaceAt( path, 1, &len, buf );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( !lstrcmpW( buf, cimv2W ), "unexpected buffer contents %s\n", wine_dbgstr_w(buf) );
    ok( len == lstrlenW( cimv2W ) + 1, "unexpected length %u\n", len );

    IWbemPath_Release( path );
}