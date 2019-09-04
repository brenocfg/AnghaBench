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
typedef  enum firewall_op { ____Placeholder_firewall_op } firewall_op ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  INetFwProfile ;
typedef  int /*<<< orphan*/  INetFwPolicy ;
typedef  int /*<<< orphan*/  INetFwMgr ;
typedef  int /*<<< orphan*/  INetFwAuthorizedApplications ;
typedef  int /*<<< orphan*/  INetFwAuthorizedApplication ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int APP_ADD ; 
 int APP_REMOVE ; 
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NetFwAuthorizedApplication ; 
 int /*<<< orphan*/  CLSID_NetFwMgr ; 
 int /*<<< orphan*/  COINIT_APARTMENTTHREADED ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CoInitializeEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int) ; 
 int /*<<< orphan*/  IID_INetFwAuthorizedApplication ; 
 int /*<<< orphan*/  IID_INetFwMgr ; 
 int /*<<< orphan*/  INetFwAuthorizedApplication_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwAuthorizedApplication_put_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INetFwAuthorizedApplication_put_ProcessImageFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INetFwAuthorizedApplications_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INetFwAuthorizedApplications_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwAuthorizedApplications_Remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INetFwMgr_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwMgr_get_LocalPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwPolicy_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwPolicy_get_CurrentProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwProfile_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwProfile_get_AuthorizedApplications (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static HRESULT set_firewall( enum firewall_op op )
{
    static const WCHAR dplaysvrW[] =
        {'d','p','l','a','y','s','v','r','.','e','x','e',0};
    static const WCHAR separator[] = {'\\',0};
    static const WCHAR clientW[] =
        {'d','p','l','a','y','_','c','l','i','e','n','t',0};
    static const WCHAR serverW[] =
        {'d','p','l','a','y','_','s','e','r','v','e','r',0};
    HRESULT hr, init;
    INetFwMgr *mgr = NULL;
    INetFwPolicy *policy = NULL;
    INetFwProfile *profile = NULL;
    INetFwAuthorizedApplication *app = NULL;
    INetFwAuthorizedApplications *apps = NULL;
    BSTR name, image = SysAllocStringLen( NULL, MAX_PATH );
    WCHAR path[MAX_PATH];

    if (!GetModuleFileNameW( NULL, image, MAX_PATH ))
    {
        SysFreeString( image );
        return E_FAIL;
    }

    if(!GetSystemDirectoryW(path, MAX_PATH))
    {
        SysFreeString( image );
        return E_FAIL;
    }
    lstrcatW(path, separator);
    lstrcatW(path, dplaysvrW);

    init = CoInitializeEx( 0, COINIT_APARTMENTTHREADED );

    hr = CoCreateInstance( &CLSID_NetFwMgr, NULL, CLSCTX_INPROC_SERVER, &IID_INetFwMgr,
                           (void **)&mgr );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = INetFwMgr_get_LocalPolicy( mgr, &policy );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = INetFwPolicy_get_CurrentProfile( policy, &profile );
    if (hr != S_OK) goto done;

    hr = INetFwProfile_get_AuthorizedApplications( profile, &apps );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = CoCreateInstance( &CLSID_NetFwAuthorizedApplication, NULL, CLSCTX_INPROC_SERVER,
                           &IID_INetFwAuthorizedApplication, (void **)&app );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    hr = INetFwAuthorizedApplication_put_ProcessImageFileName( app, image );
    if (hr != S_OK) goto done;

    name = SysAllocString( clientW );
    hr = INetFwAuthorizedApplication_put_Name( app, name );
    SysFreeString( name );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    if (op == APP_ADD)
        hr = INetFwAuthorizedApplications_Add( apps, app );
    else if (op == APP_REMOVE)
        hr = INetFwAuthorizedApplications_Remove( apps, image );
    else
        hr = E_INVALIDARG;
    if (hr != S_OK) goto done;

    INetFwAuthorizedApplication_Release( app );
    hr = CoCreateInstance( &CLSID_NetFwAuthorizedApplication, NULL, CLSCTX_INPROC_SERVER,
                           &IID_INetFwAuthorizedApplication, (void **)&app );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    SysFreeString( image );
    image = SysAllocString( path );
    hr = INetFwAuthorizedApplication_put_ProcessImageFileName( app, image );
    if (hr != S_OK) goto done;

    name = SysAllocString( serverW );
    hr = INetFwAuthorizedApplication_put_Name( app, name );
    SysFreeString( name );
    ok( hr == S_OK, "got %08x\n", hr );
    if (hr != S_OK) goto done;

    if (op == APP_ADD)
        hr = INetFwAuthorizedApplications_Add( apps, app );
    else if (op == APP_REMOVE)
        hr = INetFwAuthorizedApplications_Remove( apps, image );
    else
        hr = E_INVALIDARG;

done:
    if (app) INetFwAuthorizedApplication_Release( app );
    if (apps) INetFwAuthorizedApplications_Release( apps );
    if (policy) INetFwPolicy_Release( policy );
    if (profile) INetFwProfile_Release( profile );
    if (mgr) INetFwMgr_Release( mgr );
    if (SUCCEEDED( init )) CoUninitialize();
    SysFreeString( image );
    return hr;
}