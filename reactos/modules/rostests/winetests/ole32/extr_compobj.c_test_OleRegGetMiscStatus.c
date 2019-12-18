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
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_StdFont ; 
 int /*<<< orphan*/  CLSID_Testclass ; 
 int /*<<< orphan*/  DVASPECT_DOCPRINT ; 
 int /*<<< orphan*/  DVASPECT_ICON ; 
 int E_INVALIDARG ; 
 int OLEMISC_RECOMPOSEONRESIZE ; 
 int OleRegGetMiscStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int REGDB_E_CLASSNOTREG ; 
 int S_OK ; 
 int /*<<< orphan*/  actctx_manifest ; 
 int /*<<< orphan*/  activate_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_OleRegGetMiscStatus(void)
{
    ULONG_PTR cookie;
    HANDLE handle;
    DWORD status;
    HRESULT hr;

    hr = OleRegGetMiscStatus(&CLSID_Testclass, DVASPECT_ICON, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    status = 0xdeadbeef;
    hr = OleRegGetMiscStatus(&CLSID_Testclass, DVASPECT_ICON, &status);
    ok(hr == REGDB_E_CLASSNOTREG, "got 0x%08x\n", hr);
    ok(status == 0, "got 0x%08x\n", status);

    status = -1;
    hr = OleRegGetMiscStatus(&CLSID_StdFont, DVASPECT_ICON, &status);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(status == 0, "got 0x%08x\n", status);

    if ((handle = activate_context(actctx_manifest, &cookie)))
    {
        status = 0;
        hr = OleRegGetMiscStatus(&CLSID_Testclass, DVASPECT_ICON, &status);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(status == OLEMISC_RECOMPOSEONRESIZE, "got 0x%08x\n", status);

        /* context data takes precedence over registration info */
        status = 0;
        hr = OleRegGetMiscStatus(&CLSID_StdFont, DVASPECT_ICON, &status);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(status == OLEMISC_RECOMPOSEONRESIZE, "got 0x%08x\n", status);

        /* there's no such attribute in context */
        status = -1;
        hr = OleRegGetMiscStatus(&CLSID_Testclass, DVASPECT_DOCPRINT, &status);
        ok(hr == S_OK, "got 0x%08x\n", hr);
        ok(status == 0, "got 0x%08x\n", status);

        pDeactivateActCtx(0, cookie);
        pReleaseActCtx(handle);
    }
}