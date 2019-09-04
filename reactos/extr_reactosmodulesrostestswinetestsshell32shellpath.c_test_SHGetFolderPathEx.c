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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/ * folderId; } ;
typedef  int /*<<< orphan*/  KNOWNFOLDERID ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * E_NOT_SUFFICIENT_BUFFER ; 
 scalar_t__ FAILED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const FOLDERID_Desktop ; 
 int /*<<< orphan*/ * HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const IID_IOleObject ; 
 int KF_FLAG_DEFAULT ; 
 int KF_FLAG_DEFAULT_PATH ; 
 int KF_FLAG_DONT_UNEXPAND ; 
 int KF_FLAG_SIMPLE_IDLIST ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * S_OK ; 
 TYPE_1__* known_folders ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSHGetFolderPathEx (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pSHGetKnownFolderPath (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_SHGetFolderPathEx(void)
{
    WCHAR buffer[MAX_PATH], *path, *path2;
    unsigned int i;
    HRESULT hr;
    DWORD len;

    if (!pSHGetKnownFolderPath || !pSHGetFolderPathEx)
    {
        win_skip("SHGetKnownFolderPath or SHGetFolderPathEx not available\n");
        return;
    }

if (0) { /* crashes */
    hr = pSHGetKnownFolderPath(&FOLDERID_Desktop, 0, NULL, NULL);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got 0x%08x\n", hr);
}
    /* non-existent folder id */
    path = (void *)0xdeadbeef;
    hr = pSHGetKnownFolderPath(&IID_IOleObject, 0, NULL, &path);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "got 0x%08x\n", hr);
    ok(path == NULL, "got %p\n", path);

    path = NULL;
    hr = pSHGetKnownFolderPath(&FOLDERID_Desktop, KF_FLAG_DEFAULT_PATH, NULL, &path);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
    ok(path != NULL, "expected path != NULL\n");
    CoTaskMemFree(path);

    for (i = 0; i < ARRAY_SIZE(known_folders); ++i)
    {
        const KNOWNFOLDERID *folder_id = known_folders[i].folderId;

        path = NULL;
        hr = pSHGetKnownFolderPath(folder_id, KF_FLAG_DEFAULT, NULL, &path);
        if (FAILED(hr))
            continue;
        ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
        ok(path != NULL, "expected path != NULL\n");

        path2 = NULL;
        hr = pSHGetKnownFolderPath(folder_id, KF_FLAG_SIMPLE_IDLIST, NULL, &path2);
        ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
        ok(path2 != NULL, "expected path != NULL\n");
        ok(!lstrcmpiW(path, path2), "expected equal paths: %s, %s\n", wine_dbgstr_w(path), wine_dbgstr_w(path2));
        CoTaskMemFree(path2);

        path2 = NULL;
        hr = pSHGetKnownFolderPath(folder_id, KF_FLAG_DONT_UNEXPAND, NULL, &path2);
        ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
        ok(path2 != NULL, "expected path != NULL\n");
        ok(!lstrcmpiW(path, path2), "expected equal paths: %s, %s\n", wine_dbgstr_w(path), wine_dbgstr_w(path2));
        CoTaskMemFree(path2);

        path2 = NULL;
        hr = pSHGetKnownFolderPath(folder_id, KF_FLAG_SIMPLE_IDLIST | KF_FLAG_DONT_UNEXPAND, NULL, &path2);
        ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
        ok(path2 != NULL, "expected path != NULL\n");
        ok(!lstrcmpiW(path, path2), "expected equal paths: %s, %s\n", wine_dbgstr_w(path), wine_dbgstr_w(path2));
        CoTaskMemFree(path2);

        CoTaskMemFree(path);
    }

    path = NULL;
    hr = pSHGetKnownFolderPath(&FOLDERID_Desktop, 0, NULL, &path);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
    ok(path != NULL, "expected path != NULL\n");

    hr = pSHGetFolderPathEx(&FOLDERID_Desktop, 0, NULL, buffer, MAX_PATH);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
    ok(!lstrcmpiW(path, buffer), "expected equal paths\n");
    len = lstrlenW(buffer);
    CoTaskMemFree(path);

    hr = pSHGetFolderPathEx(&FOLDERID_Desktop, 0, NULL, buffer, 0);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got 0x%08x\n", hr);

if (0) { /* crashes */
    hr = pSHGetFolderPathEx(&FOLDERID_Desktop, 0, NULL, NULL, len + 1);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got 0x%08x\n", hr);

    hr = pSHGetFolderPathEx(NULL, 0, NULL, buffer, MAX_PATH);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got 0x%08x\n", hr);
}
    hr = pSHGetFolderPathEx(&FOLDERID_Desktop, 0, NULL, buffer, len);
    ok(hr == E_NOT_SUFFICIENT_BUFFER, "expected E_NOT_SUFFICIENT_BUFFER, got 0x%08x\n", hr);

    hr = pSHGetFolderPathEx(&FOLDERID_Desktop, 0, NULL, buffer, len + 1);
    ok(hr == S_OK, "expected S_OK, got 0x%08x\n", hr);
}