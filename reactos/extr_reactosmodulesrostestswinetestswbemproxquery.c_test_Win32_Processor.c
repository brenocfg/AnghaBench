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
 int CIM_UINT16 ; 
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
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_Processor( IWbemServices *services )
{
    static const WCHAR architectureW[] =
        {'A','r','c','h','i','t','e','c','t','u','r','e',0};
    static const WCHAR familyW[] =
        {'F','a','m','i','l','y',0};
    static const WCHAR levelW[] =
        {'L','e','v','e','l',0};
    static const WCHAR manufacturerW[] =
        {'M','a','n','u','f','a','c','t','u','r','e','r',0};
    static const WCHAR nameW[] =
        {'N','a','m','e',0};
    static const WCHAR processoridW[] =
        {'P','r','o','c','e','s','s','o','r','I','d',0};
    static const WCHAR revisionW[] =
        {'R','e','v','i','s','i','o','n',0};
    static const WCHAR versionW[] =
        {'V','e','r','s','i','o','n',0};
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'P','r','o','c','e','s','s','o','r',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *obj;
    VARIANT val;
    CIMTYPE type;
    HRESULT hr;
    DWORD count;

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    ok( hr == S_OK, "got %08x\n", hr );

    for (;;)
    {
        hr = IEnumWbemClassObject_Next( result, 10000, 1, &obj, &count );
        if (hr != S_OK) break;

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, architectureW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
        trace( "architecture %u\n", V_I4( &val ) );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, familyW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
        trace( "family %u\n", V_I4( &val ) );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, levelW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
        trace( "level %u\n", V_I4( &val ) );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, manufacturerW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "manufacturer %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, nameW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "name %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, processoridW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "processorid %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, revisionW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
        trace( "revision %u\n", V_I4( &val ) );

        type = 0xdeadbeef;
        VariantInit( &val );
        hr = IWbemClassObject_Get( obj, versionW, 0, &val, &type, NULL );
        ok( hr == S_OK, "got %08x\n", hr );
        ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
        ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
        trace( "version %s\n", wine_dbgstr_w(V_BSTR( &val )) );
        VariantClear( &val );

        IWbemClassObject_Release( obj );
    }

    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}