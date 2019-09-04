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
typedef  int /*<<< orphan*/  tmpdirA ;
typedef  int /*<<< orphan*/  pathA ;
typedef  int /*<<< orphan*/  path2A ;
typedef  int /*<<< orphan*/  buffA ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int CopyFileA (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 int GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_manifest_file (char*) ; 
 int /*<<< orphan*/  manifest_dep ; 
 int /*<<< orphan*/  manifest_main ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pActivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pDeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pReleaseActCtx (int /*<<< orphan*/ ) ; 
 int pSearchPathA (char*,char const*,char*,int,char*,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_create (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SearchPathA(void)
{
    static const CHAR testdepA[] = "testdep.dll";
    static const CHAR testdeprelA[] = "./testdep.dll";
    static const CHAR kernel32A[] = "kernel32.dll";
    static const CHAR fileA[] = "";
    CHAR pathA[MAX_PATH], buffA[MAX_PATH], path2A[MAX_PATH], path3A[MAX_PATH], curdirA[MAX_PATH];
    CHAR tmpdirA[MAX_PATH], *ptrA = NULL;
    ULONG_PTR cookie;
    HANDLE handle;
    BOOL bret;
    DWORD ret;

    if (!pSearchPathA)
    {
        win_skip("SearchPathA isn't available\n");
        return;
    }

    GetWindowsDirectoryA(pathA, sizeof(pathA)/sizeof(CHAR));

    /* NULL filename */
    SetLastError(0xdeadbeef);
    ret = pSearchPathA(pathA, NULL, NULL, sizeof(buffA)/sizeof(CHAR), buffA, &ptrA);
    ok(ret == 0, "Expected failure, got %d\n", ret);
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
      "Expected ERROR_INVALID_PARAMETER, got %x\n", GetLastError());

    /* empty filename */
    SetLastError(0xdeadbeef);
    ret = pSearchPathA(pathA, fileA, NULL, sizeof(buffA)/sizeof(CHAR), buffA, &ptrA);
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
    ret = pSearchPathA(NULL, testdepA, NULL, sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(ret == 0, "got %d\n", ret);

    ret = pSearchPathA(NULL, kernel32A, NULL, sizeof(path2A)/sizeof(CHAR), path2A, NULL);
    ok(ret && ret == strlen(path2A), "got %d\n", ret);

    ret = pActivateActCtx(handle, &cookie);
    ok(ret, "failed to activate context, %u\n", GetLastError());

    /* works when activated */
    ret = pSearchPathA(NULL, testdepA, NULL, sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(ret && ret == strlen(buffA), "got %d\n", ret);

    ret = pSearchPathA(NULL, "testdep.dll", ".ext", sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(ret && ret == strlen(buffA), "got %d\n", ret);

    ret = pSearchPathA(NULL, "testdep", ".dll", sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(ret && ret == strlen(buffA), "got %d\n", ret);

    ret = pSearchPathA(NULL, "testdep", ".ext", sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(!ret, "got %d\n", ret);

    /* name contains path */
    ret = pSearchPathA(NULL, testdeprelA, NULL, sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(!ret, "got %d\n", ret);

    /* fails with specified path that doesn't contain this file */
    ret = pSearchPathA(pathA, testdepA, NULL, sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(!ret, "got %d\n", ret);

    /* path is redirected for wellknown names too */
    ret = pSearchPathA(NULL, kernel32A, NULL, sizeof(buffA)/sizeof(CHAR), buffA, NULL);
    ok(ret && ret == strlen(buffA), "got %d\n", ret);
    ok(strcmp(buffA, path2A), "got wrong path %s, %s\n", buffA, path2A);

    ret = pDeactivateActCtx(0, cookie);
    ok(ret, "failed to deactivate context, %u\n", GetLastError());
    pReleaseActCtx(handle);

    /* test the search path priority of the working directory */
    GetTempPathA(sizeof(tmpdirA), tmpdirA);
    ret = GetCurrentDirectoryA(MAX_PATH, curdirA);
    ok(ret, "failed to obtain working directory.\n");
    sprintf(pathA, "%s\\%s", tmpdirA, kernel32A);
    ret = pSearchPathA(NULL, kernel32A, NULL, sizeof(path2A)/sizeof(CHAR), path2A, NULL);
    ok(ret && ret == strlen(path2A), "got %d\n", ret);
    bret = CopyFileA(path2A, pathA, FALSE);
    ok(bret != 0, "failed to copy test executable to temp directory, %u\n", GetLastError());
    sprintf(path3A, "%s%s%s", curdirA, curdirA[strlen(curdirA)-1] != '\\' ? "\\" : "", kernel32A);
    bret = CopyFileA(path2A, path3A, FALSE);
    ok(bret != 0, "failed to copy test executable to launch directory, %u\n", GetLastError());
    bret = SetCurrentDirectoryA(tmpdirA);
    ok(bret, "failed to change working directory\n");
    ret = pSearchPathA(NULL, kernel32A, ".exe", sizeof(buffA), buffA, NULL);
    ok(ret && ret == strlen(buffA), "got %d\n", ret);
    ok(strcmp(buffA, path3A) == 0, "expected %s, got %s\n", path3A, buffA);
    bret = SetCurrentDirectoryA(curdirA);
    ok(bret, "failed to reset working directory\n");
    DeleteFileA(path3A);
    DeleteFileA(pathA);
}