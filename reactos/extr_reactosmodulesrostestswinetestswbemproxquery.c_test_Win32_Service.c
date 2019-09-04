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
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ CIMTYPE ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 scalar_t__ CIM_STRING ; 
 scalar_t__ IWbemClassObject_Get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_ExecMethod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IWbemServices_GetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 scalar_t__ VT_BSTR ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_I4 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_UI4 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_Win32_Service( IWbemServices *services )
{
    static const WCHAR returnvalueW[] = {'R','e','t','u','r','n','V','a','l','u','e',0};
    static const WCHAR pauseserviceW[] = {'P','a','u','s','e','S','e','r','v','i','c','e',0};
    static const WCHAR resumeserviceW[] = {'R','e','s','u','m','e','S','e','r','v','i','c','e',0};
    static const WCHAR startserviceW[] = {'S','t','a','r','t','S','e','r','v','i','c','e',0};
    static const WCHAR stopserviceW[] = {'S','t','o','p','S','e','r','v','i','c','e',0};
    static const WCHAR stateW[] = {'S','t','a','t','e',0};
    static const WCHAR stoppedW[] = {'S','t','o','p','p','e','d',0};
    static const WCHAR serviceW[] = {'W','i','n','3','2','_','S','e','r','v','i','c','e','.',
        'N','a','m','e','=','"','S','p','o','o','l','e','r','"',0};
    static const WCHAR emptyW[] = {0};
    BSTR class = SysAllocString( serviceW ), empty = SysAllocString( emptyW ), method;
    IWbemClassObject *service, *out;
    VARIANT state, retval;
    CIMTYPE type;
    HRESULT hr;

    hr = IWbemServices_GetObject( services, class, 0, NULL, &service, NULL );
    if (hr != S_OK)
    {
        win_skip( "Win32_Service not available\n" );
        goto out;
    }
    type = 0xdeadbeef;
    VariantInit( &state );
    hr = IWbemClassObject_Get( service, stateW, 0, &state, &type, NULL );
    ok( hr == S_OK, "failed to get service state %08x\n", hr );
    ok( V_VT( &state ) == VT_BSTR, "unexpected variant type 0x%x\n", V_VT( &state ) );
    ok( type == CIM_STRING, "unexpected type 0x%x\n", type );

    if (!lstrcmpW( V_BSTR( &state ), stoppedW ))
    {
        out = NULL;
        method = SysAllocString( startserviceW );
        hr = IWbemServices_ExecMethod( services, class, method, 0, NULL, NULL, &out, NULL );
        ok( hr == S_OK, "failed to execute method %08x\n", hr );
        SysFreeString( method );

        VariantInit( &retval );
        hr = IWbemClassObject_Get( out, returnvalueW, 0, &retval, NULL, NULL );
        ok( hr == S_OK, "failed to get return value %08x\n", hr );
        ok( !V_I4( &retval ), "unexpected error %u\n", V_UI4( &retval ) );
        IWbemClassObject_Release( out );
    }
    out = NULL;
    method = SysAllocString( pauseserviceW );
    hr = IWbemServices_ExecMethod( services, class, method, 0, NULL, NULL, &out, NULL );
    ok( hr == S_OK, "failed to execute method %08x\n", hr );
    SysFreeString( method );

    VariantInit( &retval );
    hr = IWbemClassObject_Get( out, returnvalueW, 0, &retval, NULL, NULL );
    ok( hr == S_OK, "failed to get return value %08x\n", hr );
    ok( V_I4( &retval ), "unexpected success\n" );
    IWbemClassObject_Release( out );

    out = NULL;
    method = SysAllocString( resumeserviceW );
    hr = IWbemServices_ExecMethod( services, class, method, 0, NULL, NULL, &out, NULL );
    ok( hr == S_OK, "failed to execute method %08x\n", hr );
    SysFreeString( method );

    VariantInit( &retval );
    hr = IWbemClassObject_Get( out, returnvalueW, 0, &retval, NULL, NULL );
    ok( hr == S_OK, "failed to get return value %08x\n", hr );
    ok( V_I4( &retval ), "unexpected success\n" );
    IWbemClassObject_Release( out );

    if (!lstrcmpW( V_BSTR( &state ), stoppedW ))
    {
        out = NULL;
        method = SysAllocString( stopserviceW );
        hr = IWbemServices_ExecMethod( services, class, method, 0, NULL, NULL, &out, NULL );
        ok( hr == S_OK, "failed to execute method %08x\n", hr );
        SysFreeString( method );

        VariantInit( &retval );
        hr = IWbemClassObject_Get( out, returnvalueW, 0, &retval, NULL, NULL );
        ok( hr == S_OK, "failed to get return value %08x\n", hr );
        ok( !V_I4( &retval ), "unexpected error %u\n", V_UI4( &retval ) );
        IWbemClassObject_Release( out );
    }
    VariantClear( &state );
    IWbemClassObject_Release( service );

    service = NULL;
    hr = IWbemServices_GetObject( services, NULL, 0, NULL, &service, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    if (service) IWbemClassObject_Release( service );

    service = NULL;
    hr = IWbemServices_GetObject( services, empty, 0, NULL, &service, NULL );
    ok( hr == S_OK, "got %08x\n", hr );
    if (service) IWbemClassObject_Release( service );

out:
    SysFreeString( empty );
    SysFreeString( class );
}