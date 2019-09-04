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
typedef  int /*<<< orphan*/  ULONG ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int CIM_BOOLEAN ; 
 int CIM_FLAG_ARRAY ; 
 int CIM_STRING ; 
 int CIM_UINT16 ; 
 int IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int IWbemServices_ExecQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int SafeArrayAccessData (int /*<<< orphan*/ ,void**) ; 
 int SafeArrayGetLBound (int /*<<< orphan*/ ,int,size_t*) ; 
 int SafeArrayGetUBound (int /*<<< orphan*/ ,int,size_t*) ; 
 int SafeArrayUnaccessData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int VT_ARRAY ; 
 int VT_BOOL ; 
 int VT_BSTR ; 
 int VT_I4 ; 
 int /*<<< orphan*/  V_ARRAY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_BOOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_SystemEnclosure( IWbemServices *services )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'S','y','s','t','e','m','E','n','c','l','o','s','u','r','e',0};
    static const WCHAR captionW[] = {'C','a','p','t','i','o','n',0};
    static const WCHAR chassistypesW[] = {'C','h','a','s','s','i','s','T','y','p','e','s',0};
    static const WCHAR descriptionW[] = {'D','e','s','c','r','i','p','t','i','o','n',0};
    static const WCHAR lockpresentW[] = {'L','o','c','k','P','r','e','s','e','n','t',0};
    static const WCHAR manufacturerW[] = {'M','a','n','u','f','a','c','t','u','r','e','r',0};
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR tagW[] = {'T','a','g',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *obj;
    CIMTYPE type;
    ULONG count;
    VARIANT val;
    DWORD *data;
    HRESULT hr;

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    ok( hr == S_OK, "IWbemServices_ExecQuery failed %08x\n", hr );

    hr = IEnumWbemClassObject_Next( result, 10000, 1, &obj, &count );
    ok( hr == S_OK, "IEnumWbemClassObject_Next failed %08x\n", hr );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, captionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get caption %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "caption: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, chassistypesW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get chassis types %08x\n", hr );
    ok( V_VT( &val ) == (VT_I4|VT_ARRAY), "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == (CIM_UINT16|CIM_FLAG_ARRAY), "unexpected type 0x%x\n", type );
    hr = SafeArrayAccessData( V_ARRAY( &val ), (void **)&data );
    ok( hr == S_OK, "SafeArrayAccessData failed %x\n", hr );
    if (SUCCEEDED(hr))
    {
        LONG i, lower, upper;

        hr = SafeArrayGetLBound( V_ARRAY( &val ), 1, &lower );
        ok( hr == S_OK, "SafeArrayGetLBound failed %x\n", hr );
        hr = SafeArrayGetUBound( V_ARRAY( &val ), 1, &upper );
        ok( hr == S_OK, "SafeArrayGetUBound failed %x\n", hr );
        if (V_VT( &val ) == (VT_I4|VT_ARRAY))
        {
            for (i = 0; i < upper - lower + 1; i++)
                trace( "chassis type: %u\n", data[i] );
        }
        hr = SafeArrayUnaccessData( V_ARRAY( &val ) );
        ok( hr == S_OK, "SafeArrayUnaccessData failed %x\n", hr );
    }
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, descriptionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get description %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "description: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, lockpresentW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get lockpresent %08x\n", hr );
    ok( V_VT( &val ) == VT_BOOL, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_BOOLEAN, "unexpected type 0x%x\n", type );
    trace( "lockpresent: %u\n", V_BOOL( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, manufacturerW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get manufacturer %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "manufacturer: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, nameW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get name %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "name: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, tagW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get tag %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "tag: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    IWbemClassObject_Release( obj );
    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}