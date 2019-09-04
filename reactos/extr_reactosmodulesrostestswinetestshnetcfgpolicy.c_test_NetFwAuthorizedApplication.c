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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  INetFwAuthorizedApplication ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NetFwAuthorizedApplication ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_INetFwAuthorizedApplication ; 
 int /*<<< orphan*/  INetFwAuthorizedApplication_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ INetFwAuthorizedApplication_get_ProcessImageFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ INetFwAuthorizedApplication_put_ProcessImageFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * SysAllocStringLen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_NetFwAuthorizedApplication(void)
{
    INetFwAuthorizedApplication *app;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_NetFwAuthorizedApplication, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_INetFwAuthorizedApplication, (void**)&app);
    ok(hr == S_OK, "got: %08x\n", hr);
    if(hr == S_OK)
    {
        BSTR image = SysAllocStringLen( NULL, MAX_PATH );
        static WCHAR empty[] = {0};
        BSTR bstr;

        if (!GetModuleFileNameW( NULL, image, MAX_PATH ))
        {
            ok(0, "Failed to get filename\n");
            SysFreeString( image );
            return;
        }

        hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, NULL);
        ok(hr == E_POINTER, "got: %08x\n", hr);

        hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, &bstr);
        ok(hr == S_OK || hr == HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY), "got: %08x\n", hr);
        ok(!bstr, "got: %s\n",  wine_dbgstr_w(bstr));

        hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, NULL);
        ok(hr == E_INVALIDARG || hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got: %08x\n", hr);

        hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, empty);
        ok(hr == E_INVALIDARG || hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got: %08x\n", hr);

        hr = INetFwAuthorizedApplication_put_ProcessImageFileName(app, image);
        ok(hr == S_OK, "got: %08x\n", hr);

        hr = INetFwAuthorizedApplication_get_ProcessImageFileName(app, &bstr);
        ok(hr == S_OK, "got: %08x\n", hr);
        ok(!lstrcmpiW(bstr,image), "got: %s\n", wine_dbgstr_w(bstr));
        SysFreeString( bstr );

        SysFreeString( image );
        INetFwAuthorizedApplication_Release(app);
    }
}