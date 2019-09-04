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
typedef  int /*<<< orphan*/  IWbemServices ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  int HRESULT ;
typedef  int CIMTYPE ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int CIM_DATETIME ; 
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
 int VT_NULL ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_Bios( IWbemServices *services )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_', 'B','i','o','s',0};
    static const WCHAR descriptionW[] = {'D','e','s','c','r','i','p','t','i','o','n',0};
    static const WCHAR identificationcodeW[] = {'I','d','e','n','t','i','f','i','c','a','t','i','o','n','C','o','d','e',0};
    static const WCHAR manufacturerW[] = {'M','a','n','u','f','a','c','t','u','r','e','r',0};
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR releasedateW[] = {'R','e','l','e','a','s','e','D','a','t','e',0};
    static const WCHAR serialnumberW[] = {'S','e','r','i','a','l','N','u','m','b','e','r',0};
    static const WCHAR smbiosbiosversionW[] = {'S','M','B','I','O','S','B','I','O','S','V','e','r','s','i','o','n',0};
    static const WCHAR smbiosmajorversionW[] = {'S','M','B','I','O','S','M','a','j','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR smbiosminorversionW[] = {'S','M','B','I','O','S','M','i','n','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR versionW[] = {'V','e','r','s','i','o','n',0};
    BSTR wql = SysAllocString( wqlW ), query = SysAllocString( queryW );
    IEnumWbemClassObject *result;
    IWbemClassObject *obj;
    CIMTYPE type;
    ULONG count;
    VARIANT val;
    HRESULT hr;

    hr = IWbemServices_ExecQuery( services, wql, query, 0, NULL, &result );
    ok( hr == S_OK, "IWbemServices_ExecQuery failed %08x\n", hr );

    hr = IEnumWbemClassObject_Next( result, 10000, 1, &obj, &count );
    ok( hr == S_OK, "IEnumWbemClassObject_Next failed %08x\n", hr );

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
    hr = IWbemClassObject_Get( obj, identificationcodeW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get identication code %08x\n", hr );
    ok( V_VT( &val ) == VT_NULL, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
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
    hr = IWbemClassObject_Get( obj, releasedateW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get release date %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_DATETIME, "unexpected type 0x%x\n", type );
    trace( "release date: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, serialnumberW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get serial number %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR || V_VT( &val ) == VT_NULL /* Testbot VMs */,
        "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, smbiosbiosversionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get bios version %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "bios version: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, smbiosmajorversionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get bios major version %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
    trace( "bios major version: %u\n", V_I4( &val ) );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, smbiosminorversionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get bios minor version %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
    trace( "bios minor version: %u\n", V_I4( &val ) );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, versionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get version %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "version: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    IWbemClassObject_Release( obj );
    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}