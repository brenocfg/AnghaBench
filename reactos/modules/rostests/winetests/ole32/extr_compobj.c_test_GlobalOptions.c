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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IGlobalOptions ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_GlobalOptions ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IGlobalOptions_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IGlobalOptions ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GlobalOptions(void)
{
    IGlobalOptions *global_options;
    HRESULT hres;

    CoInitialize(NULL);

    hres = CoCreateInstance(&CLSID_GlobalOptions, NULL, CLSCTX_INPROC_SERVER,
            &IID_IGlobalOptions, (void**)&global_options);
    ok(hres == S_OK || broken(hres == E_NOINTERFACE), "CoCreateInstance(CLSID_GlobalOptions) failed: %08x\n", hres);
    if(FAILED(hres))
    {
        win_skip("CLSID_GlobalOptions not available\n");
        CoUninitialize();
        return;
    }

    IGlobalOptions_Release(global_options);

    hres = CoCreateInstance(&CLSID_GlobalOptions, (IUnknown*)0xdeadbeef, CLSCTX_INPROC_SERVER,
            &IID_IGlobalOptions, (void**)&global_options);
    ok(hres == E_INVALIDARG, "CoCreateInstance(CLSID_GlobalOptions) failed: %08x\n", hres);

    CoUninitialize();
}