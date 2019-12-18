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
typedef  int /*<<< orphan*/  pathW ;
typedef  int /*<<< orphan*/  path2W ;
typedef  int /*<<< orphan*/  buffW ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_manifest_file (char*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  manifest_dep ; 
 int /*<<< orphan*/  manifest_main ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pActivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 
 int pSearchPathW (char*,char const*,char const*,int,char*,char**) ; 
 int /*<<< orphan*/  test_create (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_SearchPathW(void)
{
    static const WCHAR testdeprelW[] = {'.','/','t','e','s','t','d','e','p','.','d','l','l',0};
    static const WCHAR testdepW[] = {'t','e','s','t','d','e','p','.','d','l','l',0};
    static const WCHAR testdep1W[] = {'t','e','s','t','d','e','p',0};
    static const WCHAR kernel32dllW[] = {'k','e','r','n','e','l','3','2','.','d','l','l',0};
    static const WCHAR kernel32W[] = {'k','e','r','n','e','l','3','2',0};
    static const WCHAR ole32W[] = {'o','l','e','3','2',0};
    static const WCHAR extW[] = {'.','e','x','t',0};
    static const WCHAR dllW[] = {'.','d','l','l',0};
    static const WCHAR fileW[] = { 0 };
    WCHAR pathW[MAX_PATH], buffW[MAX_PATH], path2W[MAX_PATH];
    WCHAR *ptrW = NULL;
    ULONG_PTR cookie;
    HANDLE handle;
    DWORD ret;

    if (!pSearchPathW)
    {
        win_skip("SearchPathW isn't available\n");
        return;
    }

if (0)
{
    /* NULL filename, crashes on nt4 */
    pSearchPathW(pathW, NULL, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, &ptrW);
}

    GetWindowsDirectoryW(pathW, sizeof(pathW)/sizeof(WCHAR));

    /* empty filename */
    SetLastError(0xdeadbeef);
    ret = pSearchPathW(pathW, fileW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, &ptrW);
    ok(ret == 0, "Expected failure, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %x\n", GetLastError());

    if (!pActivateActCtx)
        return;

    create_manifest_file("testdep1.manifest", manifest_dep);
    create_manifest_file("main.manifest", manifest_main);

    handle = test_create("main.manifest");
    delete_manifest_file("testdep1.manifest");
    delete_manifest_file("main.manifest");

    /* search fails without active context */
    ret = pSearchPathW(NULL, testdepW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret == 0, "got %d\n", ret);

    ret = pSearchPathW(NULL, kernel32dllW, NULL, sizeof(path2W)/sizeof(WCHAR), path2W, NULL);
    ok(ret && ret == lstrlenW(path2W), "got %d\n", ret);

    /* full path, name without 'dll' extension */
    GetSystemDirectoryW(pathW, sizeof(pathW)/sizeof(WCHAR));
    ret = pSearchPathW(pathW, kernel32W, NULL, sizeof(path2W)/sizeof(WCHAR), path2W, NULL);
    ok(ret == 0, "got %d\n", ret);

    GetWindowsDirectoryW(pathW, sizeof(pathW)/sizeof(WCHAR));

    ret = pActivateActCtx(handle, &cookie);
    ok(ret, "failed to activate context, %u\n", GetLastError());

    /* works when activated */
    ret = pSearchPathW(NULL, testdepW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret && ret == lstrlenW(buffW), "got %d\n", ret);

    ret = pSearchPathW(NULL, testdepW, extW, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret && ret == lstrlenW(buffW), "got %d\n", ret);

    ret = pSearchPathW(NULL, testdep1W, dllW, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret && ret == lstrlenW(buffW), "got %d\n", ret);

    ret = pSearchPathW(NULL, testdep1W, extW, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(!ret, "got %d\n", ret);

    /* name contains path */
    ret = pSearchPathW(NULL, testdeprelW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(!ret, "got %d\n", ret);

    /* fails with specified path that doesn't contain this file */
    ret = pSearchPathW(pathW, testdepW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(!ret, "got %d\n", ret);

    /* path is redirected for wellknown names too, meaning it takes precedence over normal search order */
    ret = pSearchPathW(NULL, kernel32dllW, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret && ret == lstrlenW(buffW), "got %d\n", ret);
    ok(lstrcmpW(buffW, path2W), "got wrong path %s, %s\n", wine_dbgstr_w(buffW), wine_dbgstr_w(path2W));

    /* path is built using on manifest file name */
    ret = pSearchPathW(NULL, ole32W, NULL, sizeof(buffW)/sizeof(WCHAR), buffW, NULL);
    ok(ret && ret == lstrlenW(buffW), "got %d\n", ret);

    ret = pDeactivateActCtx(0, cookie);
    ok(ret, "failed to deactivate context, %u\n", GetLastError());
    pReleaseActCtx(handle);
}