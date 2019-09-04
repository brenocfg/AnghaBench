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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int CIM_STRING ; 
 int /*<<< orphan*/  GetComputerNameW (char*,int*) ; 
 int /*<<< orphan*/  GetUserNameW (char*,int*) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemServices_ExecQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_BSTR ; 
 char* V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WBEM_E_NOT_FOUND ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_ComputerSystem( IWbemServices *services )
{
    static const WCHAR backslashW[] = {'\\',0};
    static const WCHAR memorytypeW[] = {'M','e','m','o','r','y','T','y','p','e',0};
    static const WCHAR modelW[] = {'M','o','d','e','l',0};
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR usernameW[] = {'U','s','e','r','N','a','m','e',0};
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'C','o','m','p','u','t','e','r','S','y','s','t','e','m',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *service;
    VARIANT value;
    CIMTYPE type;
    HRESULT hr;
    WCHAR compname[MAX_COMPUTERNAME_LENGTH + 1];
    WCHAR username[128];
    DWORD len, count;

    len = ARRAY_SIZE( compname );
    if (!GetComputerNameW( compname, &len ))
        compname[0] = 0;

    lstrcpyW( username, compname );
    lstrcatW( username, backslashW );
    len = ARRAY_SIZE( username ) - lstrlenW( username );
    if (!GetUserNameW( username + lstrlenW( username ), &len ))
        username[0] = 0;

    if (!compname[0] || !username[0])
    {
        skip( "Failed to get user or computer name\n" );
        goto out;
    }

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    if (hr != S_OK)
    {
        win_skip( "Win32_ComputerSystem not available\n" );
        goto out;
    }

    hr = IEnumWbemClassObject_Next( result, 10000, 1, &service, &count );
    ok( hr == S_OK, "got %08x\n", hr );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( service, memorytypeW, 0, &value, &type, NULL );
    ok( hr == WBEM_E_NOT_FOUND, "got %08x\n", hr );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( service, modelW, 0, &value, &type, NULL );
    ok( hr == S_OK, "failed to get model %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "model: %s\n", wine_dbgstr_w(V_BSTR( &value )) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( service, nameW, 0, &value, &type, NULL );
    ok( hr == S_OK, "failed to get computer name %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    ok( !lstrcmpiW( V_BSTR( &value ), compname ), "got %s, expected %s\n", wine_dbgstr_w(V_BSTR(&value)), wine_dbgstr_w(compname) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( service, usernameW, 0, &value, &type, NULL );
    ok( hr == S_OK, "failed to get computer name %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    ok( !lstrcmpiW( V_BSTR( &value ), username ), "got %s, expected %s\n", wine_dbgstr_w(V_BSTR(&value)), wine_dbgstr_w(username) );
    VariantClear( &value );

    IWbemClassObject_Release( service );
    IEnumWbemClassObject_Release( result );
out:
    SysFreeString( query );
    SysFreeString( wql );
}