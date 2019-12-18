#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * ULONG ;
struct TYPE_6__ {scalar_t__ fFlags; int /*<<< orphan*/  ViewMode; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IDropTarget ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  TYPE_2__ FOLDERSETTINGS ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * E_UNEXPECTED ; 
 int /*<<< orphan*/  FVM_ICON ; 
 int /*<<< orphan*/ * IDropTarget_DragLeave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDropTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_CDefView ; 
 int /*<<< orphan*/  IID_IDropTarget ; 
 int /*<<< orphan*/  IID_IShellView ; 
 int /*<<< orphan*/ * IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellView_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IShellView_CreateViewWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * IShellView_DestroyViewWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * IShellView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int IsWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  test_shellbrowser ; 

__attribute__((used)) static void test_CreateViewWindow(void)
{
    IShellFolder *desktop;
    HWND hwnd_view, hwnd2;
    FOLDERSETTINGS settings;
    IShellView *view;
    IDropTarget *dt;
    HRESULT hr;
    RECT r = {0};
    ULONG ref1, ref2;
    IUnknown *unk;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellView_QueryInterface(view, &IID_CDefView, (void **)&unk);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(unk == (IUnknown *)view, "got %p\n", unk);
    IUnknown_Release(unk);

if (0)
{
    /* crashes on native */
    IShellView_CreateViewWindow(view, NULL, &settings, NULL, NULL, NULL);
}

    settings.ViewMode = FVM_ICON;
    settings.fFlags = 0;
    hwnd_view = (HWND)0xdeadbeef;
    hr = IShellView_CreateViewWindow(view, NULL, &settings, NULL, NULL, &hwnd_view);
    ok(hr == E_UNEXPECTED, "got (0x%08x)\n", hr);
    ok(hwnd_view == 0, "got %p\n", hwnd_view);

    hwnd_view = (HWND)0xdeadbeef;
    hr = IShellView_CreateViewWindow(view, NULL, &settings, NULL, &r, &hwnd_view);
    ok(hr == E_UNEXPECTED, "got (0x%08x)\n", hr);
    ok(hwnd_view == 0, "got %p\n", hwnd_view);

    hwnd_view = NULL;
    hr = IShellView_CreateViewWindow(view, NULL, &settings, &test_shellbrowser, &r, &hwnd_view);
    ok(hr == S_OK || broken(hr == S_FALSE), "got (0x%08x)\n", hr);
    ok(hwnd_view != 0, "got %p\n", hwnd_view);

    hwnd2 = (HWND)0xdeadbeef;
    hr = IShellView_CreateViewWindow(view, NULL, &settings, &test_shellbrowser, &r, &hwnd2);
    ok(hr == E_UNEXPECTED, "got (0x%08x)\n", hr);
    ok(hwnd2 == NULL, "got %p\n", hwnd2);

    /* ::DragLeave without drag operation */
    hr = IShellView_QueryInterface(view, &IID_IDropTarget, (void**)&dt);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    hr = IDropTarget_DragLeave(dt);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    IDropTarget_Release(dt);

    IShellView_AddRef(view);
    ref1 = IShellView_Release(view);
    hr = IShellView_DestroyViewWindow(view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(!IsWindow(hwnd_view), "hwnd %p still valid\n", hwnd_view);
    ref2 = IShellView_Release(view);
    ok(ref1 > ref2, "expected %u > %u\n", ref1, ref2);
    ref1 = ref2;

    /* Show that releasing the shell view does not destroy the window */
    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    hwnd_view = NULL;
    hr = IShellView_CreateViewWindow(view, NULL, &settings, &test_shellbrowser, &r, &hwnd_view);
    ok(hr == S_OK || broken(hr == S_FALSE), "got (0x%08x)\n", hr);
    ok(hwnd_view != NULL, "got %p\n", hwnd_view);
    ok(IsWindow(hwnd_view), "hwnd %p still valid\n", hwnd_view);
    ref2 = IShellView_Release(view);
    ok(ref2 != 0, "ref2 = %u\n", ref2);
    ok(ref2 > ref1, "expected %u > %u\n", ref2, ref1);
    ok(IsWindow(hwnd_view), "hwnd %p still valid\n", hwnd_view);
    DestroyWindow(hwnd_view);

    IShellFolder_Release(desktop);
}