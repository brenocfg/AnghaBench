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
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int CIM_SINT32 ; 
 int CIM_STRING ; 
 int IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int IWbemServices_ExecQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int VT_BSTR ; 
 int VT_I4 ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_IP4RouteTable( IWbemServices *services )
{
    static const WCHAR destinationW[] = {'D','e','s','t','i','n','a','t','i','o','n',0};
    static const WCHAR interfaceindexW[] = {'I','n','t','e','r','f','a','c','e','I','n','d','e','x',0};
    static const WCHAR nexthopW[] = {'N','e','x','t','H','o','p',0};
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'I','P','4','R','o','u','t','e','T','a','b','l','e',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *obj;
    VARIANT val;
    CIMTYPE type;
    HRESULT hr;
    DWORD count;

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    if (hr != S_OK)
    {
        win_skip( "Win32_IP4RouteTable not available\n" );
        return;
    }

    for (;;)
    {
        hr = IEnumWbemClassObject_Next( result, 10000, 1, &obj, &count );
        if (hr != S_OK) break;

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, destinationW, 0, &val, &type, NULL );
        ok( hr == S_OK, "failed to get destination %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "destination %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, interfaceindexW, 0, &val, &type, NULL );
        ok( hr == S_OK, "failed to get interface index %08x\n", hr );
        ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_SINT32, "unexpected type 0x%x\n", type );
        trace( "interfaceindex %d\n", V_I4( &val ) );
        VariantClear( &val );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, nexthopW, 0, &val, &type, NULL );
        ok( hr == S_OK, "failed to get nexthop %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "nexthop %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        IWbemClassObject_Release( obj );
    }

    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}