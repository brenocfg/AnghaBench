#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  netpath ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * lpUniversalName; } ;
typedef  TYPE_1__ UNIVERSAL_NAME_INFOW ;
typedef  int /*<<< orphan*/  INetFwAuthorizedApplication ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NetFwAuthorizedApplication ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  GetFullPathNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetLongPathNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_INetFwAuthorizedApplication ; 
 int /*<<< orphan*/  INetFwAuthorizedApplication_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INetFwAuthorizedApplication_get_ProcessImageFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  INetFwAuthorizedApplication_put_ProcessImageFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIVERSAL_NAME_INFO_LEVEL ; 
 int /*<<< orphan*/  WNetGetUniversalNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_NetFwAuthorizedApplication(void)
{
    INetFwAuthorizedApplication *app;
    static WCHAR empty[] = {0};
    UNIVERSAL_NAME_INFOW *info;
    WCHAR fullpath[MAX_PATH];
    WCHAR netpath[MAX_PATH];
    WCHAR image[MAX_PATH];
    HRESULT hr;
    BSTR bstr;
    DWORD sz;

    hr = CoCreateInstance(&CLSID_NetFwAuthorizedApplication, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_INetFwAuthorizedApplication, (void**)&app);
    ok(hr == S_OK, "got: %08x\n", hr);

    hr = GetModuleFileNameW(NULL, image, ARRAY_SIZE(image));
    ok(hr, "GetModuleFileName failed: %u\n", GetLastError());

    hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, NULL);
    ok(hr == E_POINTER, "got: %08x\n", hr);

    hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, &bstr);
    ok(hr == S_OK || hr == HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY), "got: %08x\n", hr);
    ok(!bstr, "got: %s\n",  wine_dbgstr_w(bstr));

    hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, NULL);
    ok(hr == E_INVALIDARG || hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got: %08x\n", hr);

    hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, empty);
    ok(hr == E_INVALIDARG || hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got: %08x\n", hr);

    bstr = SysAllocString(image);
    hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, bstr);
    ok(hr == S_OK, "got: %08x\n", hr);
    SysFreeString(bstr);

    GetFullPathNameW(image, ARRAY_SIZE(fullpath), fullpath, NULL);
    GetLongPathNameW(fullpath, fullpath, ARRAY_SIZE(fullpath));

    info = (UNIVERSAL_NAME_INFOW *)&netpath;
    sz = sizeof(netpath);
    hr = WNetGetUniversalNameW(image, UNIVERSAL_NAME_INFO_LEVEL, info, &sz);
    if (hr != NO_ERROR)
    {
        info->lpUniversalName = netpath + sizeof(*info)/sizeof(WCHAR);
        lstrcpyW(info->lpUniversalName, fullpath);
    }

    hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, &bstr);
    ok(hr == S_OK, "got: %08x\n", hr);
    ok(!lstrcmpW(bstr,info->lpUniversalName), "expected %s, got %s\n",
        wine_dbgstr_w(info->lpUniversalName), wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    INetFwAuthorizedApplication_Release(app);
}