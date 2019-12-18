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
 int IWbemPath_GetClassName (int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  IWbemPath_Release (int /*<<< orphan*/ *) ; 
 int IWbemPath_SetText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_OK ; 
 int /*<<< orphan*/  WBEMPATH_CREATE_ACCEPT_ALL ; 
 int WBEM_E_INVALID_OBJECT_PATH ; 
 int WBEM_E_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * create_path () ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int lstrlenW (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  path17 ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_IWbemPath_GetClassName(void)
{
    static const WCHAR classW[] = {'W','i','n','3','2','_','L','o','g','i','c','a','l','D','i','s','k',0};
    IWbemPath *path;
    HRESULT hr;
    WCHAR buf[32];
    ULONG len;

    if (!(path = create_path())) return;

    hr = IWbemPath_GetClassName( path, NULL, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );

    len = 0;
    hr = IWbemPath_GetClassName( path, &len, NULL );
    ok( hr == WBEM_E_INVALID_OBJECT_PATH, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetClassName( path, &len, buf );
    ok( hr == WBEM_E_INVALID_OBJECT_PATH, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetClassName( path, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );
    ok( len == sizeof(buf) / sizeof(buf[0]), "unexpected length %u\n", len );

    hr = IWbemPath_SetText( path, WBEMPATH_CREATE_ACCEPT_ALL, path17 );
    ok( hr == S_OK, "got %08x\n", hr );

    len = 0;
    hr = IWbemPath_GetClassName( path, &len, NULL );
    ok( hr == S_OK, "got %08x\n", hr );

    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetClassName( path, &len, NULL );
    ok( hr == WBEM_E_INVALID_PARAMETER, "got %08x\n", hr );
    ok( len == sizeof(buf) / sizeof(buf[0]), "unexpected length %u\n", len );

    buf[0] = 0;
    len = sizeof(buf) / sizeof(buf[0]);
    hr = IWbemPath_GetClassName( path, &len, buf );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( !lstrcmpW( buf, classW ), "unexpected buffer contents %s\n", wine_dbgstr_w(buf) );
    ok( len == lstrlenW( classW ) + 1, "unexpected length %u\n", len );

    IWbemPath_Release( path );
}