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
typedef  int UINT ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolderView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  int HRESULT ;

/* Variables and functions */
 int E_FAIL ; 
 int E_NOTIMPL ; 
 int /*<<< orphan*/ * IDataObjectImpl_Construct () ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IShellFolderView ; 
 int /*<<< orphan*/  IID_IShellView ; 
 int IShellFolderView_MoveIcons (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IShellFolderView_QuerySupport (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IShellFolderView_Release (int /*<<< orphan*/ *) ; 
 int IShellFolderView_RemoveObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int IShellFolderView_SetRedraw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellView_Release (int /*<<< orphan*/ *) ; 
 int SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IShellFolderView(void)
{
    IShellFolderView *folderview;
    IShellFolder *desktop;
    IShellView *view;
    IDataObject *obj;
    UINT i;
    HRESULT hr;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellView_QueryInterface(view, &IID_IShellFolderView, (void**)&folderview);
    if (hr != S_OK)
    {
        win_skip("IShellView doesn't provide IShellFolderView on this platform\n");
        IShellView_Release(view);
        IShellFolder_Release(desktop);
        return;
    }

    /* ::MoveIcons */
    obj = IDataObjectImpl_Construct();
    hr = IShellFolderView_MoveIcons(folderview, obj);
    ok(hr == E_NOTIMPL || broken(hr == S_OK) /* W98 */, "got (0x%08x)\n", hr);
    IDataObject_Release(obj);

    /* ::SetRedraw without list created */
    hr = IShellFolderView_SetRedraw(folderview, TRUE);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    /* ::QuerySupport */
    hr = IShellFolderView_QuerySupport(folderview, NULL);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    i = 0xdeadbeef;
    hr = IShellFolderView_QuerySupport(folderview, &i);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(i == 0xdeadbeef, "got %d\n", i);

    /* ::RemoveObject */
    i = 0xdeadbeef;
    hr = IShellFolderView_RemoveObject(folderview, NULL, &i);
    ok(hr == S_OK || hr == E_FAIL, "got (0x%08x)\n", hr);
    if (hr == S_OK) ok(i == 0 || broken(i == 0xdeadbeef) /* Vista, 2k8 */,
                       "got %d\n", i);

    IShellFolderView_Release(folderview);

    IShellView_Release(view);
    IShellFolder_Release(desktop);
}