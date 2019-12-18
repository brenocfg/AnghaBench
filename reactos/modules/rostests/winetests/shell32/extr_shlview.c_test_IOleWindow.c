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
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IOleWindow ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_NOTIMPL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IOleWindow ; 
 int /*<<< orphan*/  IID_IShellView ; 
 scalar_t__ IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellView_ContextSensitiveHelp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellView_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_IOleWindow(void)
{
    IShellFolder *desktop;
    IShellView *view;
    IOleWindow *wnd;
    HRESULT hr;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellView_QueryInterface(view, &IID_IOleWindow, (void**)&wnd);
    ok(hr == E_NOINTERFACE, "got (0x%08x)\n", hr);

    /* IShellView::ContextSensitiveHelp */
    hr = IShellView_ContextSensitiveHelp(view, TRUE);
    ok(hr == E_NOTIMPL, "got (0x%08x)\n", hr);
    hr = IShellView_ContextSensitiveHelp(view, FALSE);
    ok(hr == E_NOTIMPL, "got (0x%08x)\n", hr);

    IShellView_Release(view);
    IShellFolder_Release(desktop);
}