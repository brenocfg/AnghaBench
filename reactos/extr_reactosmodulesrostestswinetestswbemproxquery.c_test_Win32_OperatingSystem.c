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
 int CIM_STRING ; 
 int CIM_UINT16 ; 
 int CIM_UINT32 ; 
 int CIM_UINT64 ; 
 int IEnumWbemClassObject_Next (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 int IWbemClassObject_BeginEnumeration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IWbemClassObject_EndEnumeration (int /*<<< orphan*/ *) ; 
 int IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int IWbemClassObject_Next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 char const* wqlW ; 

__attribute__((used)) static void test_Win32_OperatingSystem( IWbemServices *services )
{
    static const WCHAR queryW[] =
        {'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ','W','i','n','3','2','_',
         'O','p','e','r','a','t','i','n','g','S','y','s','t','e','m',0};
    static const WCHAR buildnumberW[] = {'B','u','i','l','d','N','u','m','b','e','r',0};
    static const WCHAR captionW[] = {'C','a','p','t','i','o','n',0};
    static const WCHAR csdversionW[] = {'C','S','D','V','e','r','s','i','o','n',0};
    static const WCHAR freephysicalmemoryW[] = {'F','r','e','e','P','h','y','s','i','c','a','l','M','e','m','o','r','y',0};
    static const WCHAR nameW[] = {'N','a','m','e',0};
    static const WCHAR osproductsuiteW[] = {'O','S','P','r','o','d','u','c','t','S','u','i','t','e',0};
    static const WCHAR ostypeW[] = {'O','S','T','y','p','e',0};
    static const WCHAR suitemaskW[] = {'S','u','i','t','e','M','a','s','k',0};
    static const WCHAR versionW[] = {'V','e','r','s','i','o','n',0};
    static const WCHAR servicepackmajorW[] =
        {'S','e','r','v','i','c','e','P','a','c','k','M','a','j','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR servicepackminorW[] =
        {'S','e','r','v','i','c','e','P','a','c','k','M','i','n','o','r','V','e','r','s','i','o','n',0};
    static const WCHAR totalvisiblememorysizeW[] =
        {'T','o','t','a','l','V','i','s','i','b','l','e','M','e','m','o','r','y','S','i','z','e',0};
    static const WCHAR totalvirtualmemorysizeW[] =
        {'T','o','t','a','l','V','i','r','t','u','a','l','M','e','m','o','r','y','S','i','z','e',0};
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

    hr = IWbemClassObject_BeginEnumeration( obj, 0 );
    ok( hr == S_OK, "got %08x\n", hr );

    while (IWbemClassObject_Next( obj, 0, NULL, NULL, NULL, NULL ) == S_OK) {}

    hr = IWbemClassObject_EndEnumeration( obj );
    ok( hr == S_OK, "got %08x\n", hr );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, buildnumberW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get buildnumber %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "buildnumber: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

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
    hr = IWbemClassObject_Get( obj, csdversionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get csdversion %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR || V_VT( &val ) == VT_NULL, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "csdversion: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, freephysicalmemoryW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get free physical memory size %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT64, "unexpected type 0x%x\n", type );
    trace( "freephysicalmemory %s\n", wine_dbgstr_w(V_BSTR(&val)) );
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
    hr = IWbemClassObject_Get( obj, osproductsuiteW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get osproductsuite %08x\n", hr );
    ok( V_VT( &val ) == VT_I4 || broken(V_VT( &val ) == VT_NULL) /* winxp */, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT32, "unexpected type 0x%x\n", type );
    trace( "osproductsuite: %d (%08x)\n", V_I4( &val ), V_I4( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, ostypeW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get ostype %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
    trace( "ostype: %d\n", V_I4( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, servicepackmajorW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get servicepackmajor %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
    trace( "servicepackmajor: %d\n", V_I4( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, servicepackminorW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get servicepackminor %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT16, "unexpected type 0x%x\n", type );
    trace( "servicepackminor: %d\n", V_I4( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, suitemaskW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get suitemask %08x\n", hr );
    ok( V_VT( &val ) == VT_I4, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT32, "unexpected type 0x%x\n", type );
    trace( "suitemask: %d (%08x)\n", V_I4( &val ), V_I4( &val ) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, versionW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get version %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );
    trace( "version: %s\n", wine_dbgstr_w(V_BSTR( &val )) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, totalvisiblememorysizeW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get visible memory size %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT64, "unexpected type 0x%x\n", type );
    trace( "totalvisiblememorysize %s\n", wine_dbgstr_w(V_BSTR(&val)) );
    VariantClear( &val );

    type = 0xdeadbeef;
    VariantInit( &val );
    hr = IWbemClassObject_Get( obj, totalvirtualmemorysizeW, 0, &val, &type, NULL );
    ok( hr == S_OK, "failed to get virtual memory size %08x\n", hr );
    ok( V_VT( &val ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &val ) );
    ok( type == CIM_UINT64, "unexpected type 0x%x\n", type );
    trace( "totalvirtualmemorysize %s\n", wine_dbgstr_w(V_BSTR(&val)) );
    VariantClear( &val );

    IWbemClassObject_Release( obj );
    IEnumWbemClassObject_Release( result );
    SysFreeString( query );
    SysFreeString( wql );
}