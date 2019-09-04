#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int LowPart; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  IUriBuilderFactory ;
typedef  int /*<<< orphan*/  IUriBuilder ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IPersistStream ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CUri ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int E_UNEXPECTED ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 int /*<<< orphan*/  IID_IUri ; 
 int /*<<< orphan*/  IID_IUriBuilderFactory ; 
 int IPersistStream_GetSizeMax (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int IPersistStream_IsDirty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStream_Release (int /*<<< orphan*/ *) ; 
 int IUriBuilderFactory_CreateIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IUriBuilderFactory_CreateInitializedIUriBuilder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUriBuilderFactory_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUriBuilder_Release (int /*<<< orphan*/ *) ; 
 int IUri_GetAbsoluteUri (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetAuthority (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetDisplayUri (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetDomain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetExtension (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetFragment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetHost (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetHostType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetPassword (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetPathAndQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetPort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetPropertyBSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IUri_GetPropertyDWORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IUri_GetPropertyLength (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IUri_GetQuery (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetRawUri (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetScheme (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetSchemeName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetUserInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetUserName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_GetZone (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_IsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IUri_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  Uri_PROPERTY_PORT ; 
 int /*<<< orphan*/  Uri_PROPERTY_RAW_URI ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_UninitializedUri(void)
{
    IUri *uri;
    IUriBuilderFactory *ubf;
    IPersistStream *ps;
    IUriBuilder *ub;
    BSTR bstr;
    DWORD dword;
    BOOL eq;
    ULARGE_INTEGER ui;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_CUri, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IUri, (void**)&uri);
    if(FAILED(hr)) {
        win_skip("Skipping uninitialized Uri tests.\n");
        return;
    }

    hr = IUri_QueryInterface(uri, &IID_IUriBuilderFactory, (void**)&ubf);
    ok(hr == S_OK, "QueryInterface(IID_IUriBuillderFactory) failed: %x.\n", hr);
    hr = IUri_QueryInterface(uri, &IID_IPersistStream, (void**)&ps);
    ok(hr == S_OK, "QueryInterface(IID_IPersistStream) failed: %x.\n", hr);

    hr = IUri_GetAbsoluteUri(uri, NULL);
    ok(hr == E_UNEXPECTED, "GetAbsoluteUri returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetAbsoluteUri(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetAbsoluteUri returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetAuthority(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetAuthority returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetDisplayUri(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetDisplayUri returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetDomain(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetDomain returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetExtension(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetExtension returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetFragment(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetFragment returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetHost(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetHost returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetHostType(uri, &dword);
    ok(hr == E_UNEXPECTED, "GetHostType returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPassword(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetPassword returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPassword(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetPassword returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPathAndQuery(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetPathAndQuery returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPort(uri, &dword);
    ok(hr == E_UNEXPECTED, "GetPort returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetProperties(uri, &dword);
    ok(hr == E_UNEXPECTED, "GetProperties returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPropertyBSTR(uri, Uri_PROPERTY_RAW_URI, &bstr, 0);
    ok(hr == E_UNEXPECTED, "GetPropertyBSTR returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPropertyDWORD(uri, Uri_PROPERTY_PORT, &dword, 0);
    ok(hr == E_UNEXPECTED, "GetPropertyDWORD returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetPropertyLength(uri, Uri_PROPERTY_RAW_URI, &dword, 0);
    ok(hr == E_UNEXPECTED, "GetPropertyLength returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetQuery(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetQuery returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetRawUri(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetRawUri returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetScheme(uri, &dword);
    ok(hr == E_UNEXPECTED, "GetScheme returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetSchemeName(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetSchemeName returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetUserInfo(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetUserInfo returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetUserName(uri, &bstr);
    ok(hr == E_UNEXPECTED, "GetUserName returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_GetZone(uri, &dword);
    ok(hr == E_UNEXPECTED, "GetZone returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUri_IsEqual(uri, uri, &eq);
    ok(hr == E_UNEXPECTED, "IsEqual returned %x, expected E_UNEXPECTED.\n", hr);

    hr = IUriBuilderFactory_CreateInitializedIUriBuilder(ubf, 0, 0, &ub);
    ok(hr == E_UNEXPECTED, "CreateInitializedIUriBuilder returned %x, expected E_UNEXPECTED.\n", hr);
    hr = IUriBuilderFactory_CreateIUriBuilder(ubf, 0, 0, &ub);
    ok(hr == S_OK, "CreateIUriBuilder returned %x, expected S_OK.\n", hr);
    IUriBuilder_Release(ub);

    hr = IPersistStream_GetSizeMax(ps, &ui);
    ok(hr == S_OK, "GetSizeMax returned %x, expected S_OK.\n", hr);
    ok(ui.u.LowPart == 34, "ui.LowPart = %d, expected 34.\n", ui.u.LowPart);
    hr = IPersistStream_IsDirty(ps);
    ok(hr == S_FALSE, "IsDirty returned %x, expected S_FALSE.\n", hr);

    IPersistStream_Release(ps);
    IUriBuilderFactory_Release(ubf);
    IUri_Release(uri);
}