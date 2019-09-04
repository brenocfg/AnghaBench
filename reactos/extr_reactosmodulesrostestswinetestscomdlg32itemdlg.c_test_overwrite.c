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
typedef  char WCHAR ;
struct TYPE_3__ {char const* set_filename; int OnOverwrite; int OnFileOk; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  TYPE_1__ IFileDialogEventsImpl ;
typedef  int /*<<< orphan*/  IFileDialogEvents ;
typedef  int /*<<< orphan*/  IFileDialog ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FileOpenDialog ; 
 int /*<<< orphan*/  CLSID_FileSaveDialog ; 
 int CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (char const*) ; 
 int FOS_NOCHANGEDIR ; 
 int FOS_NOREADONLYRETURN ; 
 int FOS_OVERWRITEPROMPT ; 
 int FOS_PATHMUSTEXIST ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int /*<<< orphan*/ * IFileDialogEvents_Constructor () ; 
 int /*<<< orphan*/  IFileDialogEvents_Release (int /*<<< orphan*/ *) ; 
 int IFileDialog_Advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IFileDialog_GetFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFileDialog_Release (int /*<<< orphan*/ *) ; 
 int IFileDialog_SetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IFileDialog_SetOptions (int /*<<< orphan*/ *,int) ; 
 int IFileDialog_Show (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IFileDialog_Unadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IFileDialog ; 
 int /*<<< orphan*/  IID_IShellItem ; 
 int /*<<< orphan*/  IShellItem_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int S_OK ; 
 TYPE_1__* impl_from_IFileDialogEvents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pSHCreateItemFromParsingName (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  touch_file (char const*) ; 
 int wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_overwrite(void)
{
    static const WCHAR filename_winetest[] = {'w','i','n','e','t','e','s','t','.','o','v','w',0};
    IFileDialogEventsImpl *pfdeimpl;
    IFileDialogEvents *pfde;
    IFileDialog *fd;
    DWORD cookie;
    LPWSTR filename;
    IShellItem *psi_current;
    WCHAR buf[MAX_PATH];
    HRESULT hr;

    GetCurrentDirectoryW(MAX_PATH, buf);
    ok(!!pSHCreateItemFromParsingName, "SHCreateItemFromParsingName is missing.\n");
    hr = pSHCreateItemFromParsingName(buf, NULL, &IID_IShellItem, (void**)&psi_current);
    ok(hr == S_OK, "Got 0x%08x\n", hr);

    touch_file(filename_winetest);

    /* FOS_OVERWRITEPROMPT has no effect on open dialog */
    hr = CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&fd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetOptions(fd, FOS_OVERWRITEPROMPT | FOS_NOCHANGEDIR);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetFolder(fd, psi_current);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    pfde = IFileDialogEvents_Constructor();
    pfdeimpl = impl_from_IFileDialogEvents(pfde);
    pfdeimpl->set_filename = filename_winetest;
    hr = IFileDialog_Advise(fd, pfde, &cookie);
    ok(hr == S_OK, "Advise failed: Got 0x%08x\n", hr);

    hr = IFileDialog_Show(fd, NULL);
    ok(hr == S_OK, "Show failed: Got 0x%08x\n", hr);

    ok(!pfdeimpl->OnOverwrite, "got %u overwrite events\n", pfdeimpl->OnOverwrite);
    ok(pfdeimpl->OnFileOk == 1, "got %u ok events\n", pfdeimpl->OnFileOk);

    hr = IFileDialog_GetFileName(fd, &filename);
    ok(hr == S_OK, "GetFileName failed: Got 0x%08x\n", hr);
    ok(!lstrcmpW(filename, filename_winetest), "Got %s\n", wine_dbgstr_w(filename));
    CoTaskMemFree(filename);

    hr = IFileDialog_Unadvise(fd, cookie);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    IFileDialog_Release(fd);

    IFileDialogEvents_Release(pfde);

    /* Save dialog doesn't check for overwrite without FOS_OVERWRITEPROMPT set */
    hr = CoCreateInstance(&CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&fd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetOptions(fd, FOS_NOREADONLYRETURN | FOS_PATHMUSTEXIST | FOS_NOCHANGEDIR);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetFolder(fd, psi_current);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    pfde = IFileDialogEvents_Constructor();
    pfdeimpl = impl_from_IFileDialogEvents(pfde);
    pfdeimpl->set_filename = filename_winetest;
    hr = IFileDialog_Advise(fd, pfde, &cookie);
    ok(hr == S_OK, "Advise failed: Got 0x%08x\n", hr);

    hr = IFileDialog_Show(fd, NULL);
    ok(hr == S_OK, "Show failed: Got 0x%08x\n", hr);

    ok(!pfdeimpl->OnOverwrite, "got %u overwrite events\n", pfdeimpl->OnOverwrite);
    ok(pfdeimpl->OnFileOk == 1, "got %u ok events\n", pfdeimpl->OnFileOk);

    hr = IFileDialog_GetFileName(fd, &filename);
    ok(hr == S_OK, "GetFileName failed: Got 0x%08x\n", hr);
    ok(!lstrcmpW(filename, filename_winetest), "Got %s\n", wine_dbgstr_w(filename));
    CoTaskMemFree(filename);

    hr = IFileDialog_Unadvise(fd, cookie);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    IFileDialog_Release(fd);

    IFileDialogEvents_Release(pfde);

    /* Save dialog with FOS_OVERWRITEPROMPT set */
    hr = CoCreateInstance(&CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&fd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetFolder(fd, psi_current);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    pfde = IFileDialogEvents_Constructor();
    pfdeimpl = impl_from_IFileDialogEvents(pfde);
    pfdeimpl->set_filename = filename_winetest;
    hr = IFileDialog_Advise(fd, pfde, &cookie);
    ok(hr == S_OK, "Advise failed: Got 0x%08x\n", hr);

    hr = IFileDialog_Show(fd, NULL);
    ok(hr == S_OK, "Show failed: Got 0x%08x\n", hr);

    ok(pfdeimpl->OnOverwrite == 1, "got %u overwrite events\n", pfdeimpl->OnOverwrite);
    ok(pfdeimpl->OnFileOk == 1, "got %u ok events\n", pfdeimpl->OnFileOk);

    hr = IFileDialog_GetFileName(fd, &filename);
    ok(hr == S_OK, "GetFileName failed: Got 0x%08x\n", hr);
    ok(!lstrcmpW(filename, filename_winetest), "Got %s\n", wine_dbgstr_w(filename));
    CoTaskMemFree(filename);

    hr = IFileDialog_Unadvise(fd, cookie);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    IFileDialog_Release(fd);

    IFileDialogEvents_Release(pfde);

    DeleteFileW(filename_winetest);

    /* Save dialog with FOS_OVERWRITEPROMPT set but without existing file */
    hr = CoCreateInstance(&CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IFileDialog, (void**)&fd);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    hr = IFileDialog_SetFolder(fd, psi_current);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    pfde = IFileDialogEvents_Constructor();
    pfdeimpl = impl_from_IFileDialogEvents(pfde);
    pfdeimpl->set_filename = filename_winetest;
    hr = IFileDialog_Advise(fd, pfde, &cookie);
    ok(hr == S_OK, "Advise failed: Got 0x%08x\n", hr);

    hr = IFileDialog_Show(fd, NULL);
    ok(hr == S_OK, "Show failed: Got 0x%08x\n", hr);

    ok(!pfdeimpl->OnOverwrite, "got %u overwrite events\n", pfdeimpl->OnOverwrite);
    ok(pfdeimpl->OnFileOk == 1, "got %u ok events\n", pfdeimpl->OnFileOk);

    hr = IFileDialog_GetFileName(fd, &filename);
    ok(hr == S_OK, "GetFileName failed: Got 0x%08x\n", hr);
    ok(!lstrcmpW(filename, filename_winetest), "Got %s\n", wine_dbgstr_w(filename));
    CoTaskMemFree(filename);

    hr = IFileDialog_Unadvise(fd, cookie);
    ok(hr == S_OK, "got 0x%08x.\n", hr);

    IFileDialog_Release(fd);

    IFileDialogEvents_Release(pfde);

    IShellItem_Release(psi_current);
}