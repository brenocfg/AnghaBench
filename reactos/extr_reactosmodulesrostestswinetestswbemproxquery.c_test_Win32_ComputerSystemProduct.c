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
 int VT_NULL ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_ComputerSystemProduct( IWbemServices *services )
{
    static const WCHAR identifyingnumberW[] =
        {'I','d','e','n','t','i','f','y','i','n','g','N','u','m','b','e','r',0};
    static const WCHAR nameW[] =
        {'N','a','m','e',0};
    static const WCHAR skunumberW[] =
        {'S','K','U','N','u','m','b','e','r',0};
    static const WCHAR uuidW[] =
        {'U','U','I','D',0};
    static const WCHAR vendorW[] =
        {'V','e','n','d','o','r',0};
    static const WCHAR versionW[] =
        {'V','e','r','s','i','o','n',0};
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'C','o','m','p','u','t','e','r','S','y','s','t','e','m','P','r','o','d','u','c','t',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *obj;
    VARIANT value;
    CIMTYPE type;
    HRESULT hr;
    DWORD count;

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    if (hr != S_OK)
    {
        win_skip( "Win32_ComputerSystemProduct not available\n" );
        return;
    }

    hr = IEnumWbemClassObject_Next( result, 10000, 1, &obj, &count );
    ok( hr == S_OK, "got %08x\n", hr );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, identifyingnumberW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "identifyingnumber %s\n", wine_dbgstr_w(V_BSTR(&value)) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, nameW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "name %s\n", wine_dbgstr_w(V_BSTR(&value)) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, skunumberW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_NULL, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, uuidW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "uuid %s\n", wine_dbgstr_w(V_BSTR(&value)) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, vendorW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "vendor %s\n", wine_dbgstr_w(V_BSTR(&value)) );
    VariantClear( &value );

    type = 0xdeadbeef;
    VariantInit( &value );
    hr = IWbemClassObject_Get( obj, versionW, 0, &value, &type, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    ok( V_VT( &value ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &value ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "version %s\n", wine_dbgstr_w(V_BSTR(&value)) );
    VariantClear( &value );

    IWbemClassObject_Release( obj );
    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}