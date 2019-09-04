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
struct TYPE_3__ {int cmdID; } ;
typedef  TYPE_1__ OLECMD ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IID_IShellView ; 
 scalar_t__ IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IOleCommandTarget_QueryStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellView_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ OLECMDERR_E_UNKNOWNGROUP ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_IOleCommandTarget(void)
{
    IShellFolder *psf_desktop;
    IShellView *psv;
    IOleCommandTarget *poct;
    HRESULT hr;

    hr = SHGetDesktopFolder(&psf_desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(psf_desktop, NULL, &IID_IShellView, (void**)&psv);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    if(SUCCEEDED(hr))
    {
        hr = IShellView_QueryInterface(psv, &IID_IOleCommandTarget, (void**)&poct);
        ok(hr == S_OK || broken(hr == E_NOINTERFACE) /* Win95/NT4 */, "Got 0x%08x\n", hr);
        if(SUCCEEDED(hr))
        {
            OLECMD oc;

            hr = IOleCommandTarget_QueryStatus(poct, NULL, 0, NULL, NULL);
            ok(hr == E_INVALIDARG, "Got 0x%08x\n", hr);

            oc.cmdID = 1;
            hr = IOleCommandTarget_QueryStatus(poct, NULL, 0, &oc, NULL);
            ok(hr == OLECMDERR_E_UNKNOWNGROUP, "Got 0x%08x\n", hr);

            oc.cmdID = 1;
            hr = IOleCommandTarget_QueryStatus(poct, NULL, 1, &oc, NULL);
            ok(hr == OLECMDERR_E_UNKNOWNGROUP, "Got 0x%08x\n", hr);

            hr = IOleCommandTarget_Exec(poct, NULL, 0, 0, NULL, NULL);
            ok(hr == OLECMDERR_E_UNKNOWNGROUP, "Got 0x%08x\n", hr);

            IOleCommandTarget_Release(poct);
        }

        IShellView_Release(psv);
    }

    IShellFolder_Release(psf_desktop);
}