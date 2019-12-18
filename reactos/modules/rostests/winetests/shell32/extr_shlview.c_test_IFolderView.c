#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ count; } ;
struct TYPE_9__ {scalar_t__ fFlags; int /*<<< orphan*/  ViewMode; } ;
struct TYPE_8__ {void* x; void* y; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  void* PITEMID_CHILD ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IShellBrowser ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  IFolderView2 ;
typedef  int /*<<< orphan*/  IFolderView ;
typedef  void* HWND ;
typedef  void* HRESULT ;
typedef  TYPE_2__ FOLDERSETTINGS ;

/* Variables and functions */
 void* E_FAIL ; 
 void* E_INVALIDARG ; 
 void* E_POINTER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FVM_ICON ; 
 void* HIWORD (scalar_t__) ; 
 int /*<<< orphan*/  IFolderView2_Release (int /*<<< orphan*/ *) ; 
 void* IFolderView_GetFocusedItem (int /*<<< orphan*/ *,scalar_t__*) ; 
 void* IFolderView_GetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 void* IFolderView_GetSelectionMarkedItem (int /*<<< orphan*/ *,scalar_t__*) ; 
 void* IFolderView_GetSpacing (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* IFolderView_Item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IFolderView_ItemCount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 void* IFolderView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFolderView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFolderView ; 
 int /*<<< orphan*/  IID_IFolderView2 ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  IID_IShellView ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/ * IShellBrowserImpl_Construct () ; 
 int /*<<< orphan*/  IShellBrowser_Release (int /*<<< orphan*/ *) ; 
 void* IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 void* IShellView_CreateViewWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 void* IShellView_DestroyViewWindow (int /*<<< orphan*/ *) ; 
 void* IShellView_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int IsWindow (void*) ; 
 size_t LISTVIEW_SEQ_INDEX ; 
 void* LOWORD (scalar_t__) ; 
 int /*<<< orphan*/  LVM_GETITEMSPACING ; 
 int /*<<< orphan*/  NUM_MSG_SEQUENCES ; 
 void* SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SVGIO_ALLVIEW ; 
 void* S_FALSE ; 
 void* S_OK ; 
 scalar_t__ SendMessageA (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  empty_seq ; 
 int /*<<< orphan*/  flush_sequences (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  folderview_getfocused_seq ; 
 int /*<<< orphan*/  folderview_getselectionmarked_seq ; 
 int /*<<< orphan*/  folderview_getspacing_seq ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_sequence (TYPE_3__**,size_t,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__** sequences ; 
 void* subclass_listview (void*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_IFolderView(void)
{
    IShellFolder *desktop, *folder;
    FOLDERSETTINGS settings;
    IShellView *view;
    IShellBrowser *browser;
    IFolderView2 *fv2;
    IFolderView *fv;
    IUnknown *unk;
    HWND hwnd_view, hwnd_list;
    PITEMID_CHILD pidl;
    HRESULT hr;
    INT ret, count;
    POINT pt;
    RECT r;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellView_QueryInterface(view, &IID_IFolderView, (void**)&fv);
    if (hr != S_OK)
    {
        win_skip("IFolderView not supported by desktop folder\n");
        IShellView_Release(view);
        IShellFolder_Release(desktop);
        return;
    }

    /* call methods before window creation */
    hr = IFolderView_GetSpacing(fv, NULL);
    ok(hr == S_FALSE || broken(hr == S_OK) /* win7 */, "got (0x%08x)\n", hr);

    pidl = (void*)0xdeadbeef;
    hr = IFolderView_Item(fv, 0, &pidl);
    ok(hr == E_INVALIDARG || broken(hr == E_FAIL) /* < Vista */, "got (0x%08x)\n", hr);
    ok(pidl == 0 || broken(pidl == (void*)0xdeadbeef) /* < Vista */, "got %p\n", pidl);

if (0)
{
    /* crashes on Vista and Win2k8 - List not created yet case */
    IFolderView_GetSpacing(fv, &pt);

    /* crashes on XP */
    IFolderView_GetSelectionMarkedItem(fv, NULL);
    IFolderView_GetFocusedItem(fv, NULL);

    /* crashes on Vista+ */
    IFolderView_Item(fv, 0, NULL);
}

    browser = IShellBrowserImpl_Construct();

    settings.ViewMode = FVM_ICON;
    settings.fFlags = 0;
    hwnd_view = (HWND)0xdeadbeef;
    SetRect(&r, 0, 0, 100, 100);
    hr = IShellView_CreateViewWindow(view, NULL, &settings, browser, &r, &hwnd_view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(IsWindow(hwnd_view), "got %p\n", hwnd_view);

    hwnd_list = subclass_listview(hwnd_view);
    if (!hwnd_list)
    {
        win_skip("Failed to subclass ListView control\n");
        IShellBrowser_Release(browser);
        IFolderView_Release(fv);
        IShellView_Release(view);
        IShellFolder_Release(desktop);
        return;
    }

    /* IFolderView::GetSpacing */
    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    hr = IFolderView_GetSpacing(fv, NULL);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok_sequence(sequences, LISTVIEW_SEQ_INDEX, empty_seq, "IFolderView::GetSpacing, empty", FALSE);

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    hr = IFolderView_GetSpacing(fv, &pt);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    /* fails with empty sequence on win7 for unknown reason */
    if (sequences[LISTVIEW_SEQ_INDEX]->count)
    {
        ok_sequence(sequences, LISTVIEW_SEQ_INDEX, folderview_getspacing_seq, "IFolderView::GetSpacing", FALSE);
        ok(pt.x > 0, "got %d\n", pt.x);
        ok(pt.y > 0, "got %d\n", pt.y);
        ret = SendMessageA(hwnd_list, LVM_GETITEMSPACING, 0, 0);
        ok(pt.x == LOWORD(ret) && pt.y == HIWORD(ret), "got (%d, %d)\n", LOWORD(ret), HIWORD(ret));
    }

    /* IFolderView::ItemCount */
if (0)
{
    /* crashes on XP */
    IFolderView_ItemCount(fv, SVGIO_ALLVIEW, NULL);
}

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    IFolderView_ItemCount(fv, SVGIO_ALLVIEW, &count);

    /* IFolderView::GetSelectionMarkedItem */
if (0)
{
    /* crashes on XP */
    IFolderView_GetSelectionMarkedItem(fv, NULL);
}

    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    hr = IFolderView_GetSelectionMarkedItem(fv, &ret);
    if (count)
        ok(hr == S_OK, "got (0x%08x)\n", hr);
    else
        ok(hr == S_FALSE, "got (0x%08x)\n", hr);
    ok_sequence(sequences, LISTVIEW_SEQ_INDEX, folderview_getselectionmarked_seq,
                "IFolderView::GetSelectionMarkedItem", FALSE);

    /* IFolderView::GetFocusedItem */
    flush_sequences(sequences, NUM_MSG_SEQUENCES);
    hr = IFolderView_GetFocusedItem(fv, &ret);
    if (count)
        ok(hr == S_OK, "got (0x%08x)\n", hr);
    else
        ok(hr == S_FALSE, "got (0x%08x)\n", hr);
    ok_sequence(sequences, LISTVIEW_SEQ_INDEX, folderview_getfocused_seq,
                "IFolderView::GetFocusedItem", FALSE);

    /* IFolderView::GetFolder, just return pointer */
if (0)
{
    /* crashes on XP */
    IFolderView_GetFolder(fv, NULL, (void**)&folder);
    IFolderView_GetFolder(fv, NULL, NULL);
}

    hr = IFolderView_GetFolder(fv, &IID_IShellFolder, NULL);
    ok(hr == E_POINTER, "got (0x%08x)\n", hr);

    hr = IFolderView_GetFolder(fv, &IID_IShellFolder, (void**)&folder);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(desktop == folder, "\n");
    if (folder) IShellFolder_Release(folder);

    hr = IFolderView_GetFolder(fv, &IID_IUnknown, (void**)&unk);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    if (unk) IUnknown_Release(unk);

    hr = IFolderView_QueryInterface(fv, &IID_IFolderView2, (void**)&fv2);
    if (hr != S_OK)
        win_skip("IFolderView2 is not supported.\n");
    if (fv2) IFolderView2_Release(fv2);

    hr = IShellView_DestroyViewWindow(view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ok(!IsWindow(hwnd_view), "hwnd %p still valid\n", hwnd_view);

    IShellBrowser_Release(browser);
    IFolderView_Release(fv);
    IShellView_Release(view);
    IShellFolder_Release(desktop);
}