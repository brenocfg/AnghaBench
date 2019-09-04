#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cFileName; int /*<<< orphan*/ * cAlternateFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FINDEX_SEARCH_OPS ;
typedef  scalar_t__ FINDEX_INFO_LEVELS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NO_MORE_FILES ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 int FIND_FIRST_EX_CASE_SENSITIVE ; 
 int FIND_FIRST_EX_LARGE_FETCH ; 
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindExInfoBasic ; 
 int /*<<< orphan*/  FindExSearchLimitToDirectories ; 
 int /*<<< orphan*/  FindNextFileA (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  _lclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lcreat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFindFirstFileExA (char*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  trace (char*,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FindFirstFileExA(FINDEX_INFO_LEVELS level, FINDEX_SEARCH_OPS search_ops, DWORD flags)
{
    WIN32_FIND_DATAA search_results;
    HANDLE handle;
    BOOL ret;

    if (!pFindFirstFileExA)
    {
        win_skip("FindFirstFileExA() is missing\n");
        return;
    }

    trace("Running FindFirstFileExA tests with level=%d, search_ops=%d, flags=%u\n",
          level, search_ops, flags);

    CreateDirectoryA("test-dir", NULL);
    _lclose(_lcreat("test-dir\\file1", 0));
    _lclose(_lcreat("test-dir\\file2", 0));
    CreateDirectoryA("test-dir\\dir1", NULL);
    SetLastError(0xdeadbeef);
    handle = pFindFirstFileExA("test-dir\\*", level, &search_results, search_ops, NULL, flags);
    if (handle == INVALID_HANDLE_VALUE && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("FindFirstFileExA is not implemented\n");
        goto cleanup;
    }
    if ((flags & FIND_FIRST_EX_LARGE_FETCH) && handle == INVALID_HANDLE_VALUE && GetLastError() == ERROR_INVALID_PARAMETER)
    {
        win_skip("FindFirstFileExA flag FIND_FIRST_EX_LARGE_FETCH not supported, skipping test\n");
        goto cleanup;
    }
    if ((level == FindExInfoBasic) && handle == INVALID_HANDLE_VALUE && GetLastError() == ERROR_INVALID_PARAMETER)
    {
        win_skip("FindFirstFileExA level FindExInfoBasic not supported, skipping test\n");
        goto cleanup;
    }

#define CHECK_NAME(fn) (strcmp((fn), "file1") == 0 || strcmp((fn), "file2") == 0 || strcmp((fn), "dir1") == 0)
#define CHECK_LEVEL(fn) (level != FindExInfoBasic || !(fn)[0])

    ok(handle != INVALID_HANDLE_VALUE, "FindFirstFile failed (err=%u)\n", GetLastError());
    ok(strcmp(search_results.cFileName, ".") == 0, "First entry should be '.', is %s\n", search_results.cFileName);
    ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

    ok(FindNextFileA(handle, &search_results), "Fetching second file failed\n");
    ok(strcmp(search_results.cFileName, "..") == 0, "Second entry should be '..' is %s\n", search_results.cFileName);
    ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

    ok(FindNextFileA(handle, &search_results), "Fetching third file failed\n");
    ok(CHECK_NAME(search_results.cFileName), "Invalid third entry - %s\n", search_results.cFileName);
    ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

    SetLastError(0xdeadbeef);
    ret = FindNextFileA(handle, &search_results);
    if (!ret && (GetLastError() == ERROR_NO_MORE_FILES) && (search_ops == FindExSearchLimitToDirectories))
    {
        skip("File system supports directory filtering\n");
        /* Results from the previous call are not cleared */
        ok(strcmp(search_results.cFileName, "dir1") == 0, "Third entry should be 'dir1' is %s\n", search_results.cFileName);
        ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

    }
    else
    {
        ok(ret, "Fetching fourth file failed\n");
        ok(CHECK_NAME(search_results.cFileName), "Invalid fourth entry - %s\n", search_results.cFileName);
        ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

        ok(FindNextFileA(handle, &search_results), "Fetching fifth file failed\n");
        ok(CHECK_NAME(search_results.cFileName), "Invalid fifth entry - %s\n", search_results.cFileName);
        ok(CHECK_LEVEL(search_results.cAlternateFileName), "FindFirstFile unexpectedly returned an alternate filename\n");

        ok(FindNextFileA(handle, &search_results) == FALSE, "Fetching sixth file should fail\n");
    }

#undef CHECK_NAME
#undef CHECK_LEVEL

    FindClose( handle );

    /* Most Windows systems seem to ignore the FIND_FIRST_EX_CASE_SENSITIVE flag. Unofficial documentation
     * suggests that there are registry keys and that it might depend on the used filesystem. */
    SetLastError(0xdeadbeef);
    handle = pFindFirstFileExA("TEST-DIR\\*", level, &search_results, search_ops, NULL, flags);
    if (flags & FIND_FIRST_EX_CASE_SENSITIVE)
    {
        ok(handle != INVALID_HANDLE_VALUE || GetLastError() == ERROR_PATH_NOT_FOUND,
           "Unexpected error %x, expected valid handle or ERROR_PATH_NOT_FOUND\n", GetLastError());
        trace("FindFirstFileExA flag FIND_FIRST_EX_CASE_SENSITIVE is %signored\n",
              (handle == INVALID_HANDLE_VALUE) ? "not " : "");
    }
    else
        ok(handle != INVALID_HANDLE_VALUE, "Unexpected error %x, expected valid handle\n", GetLastError());
    if (handle != INVALID_HANDLE_VALUE)
        FindClose( handle );

cleanup:
    DeleteFileA("test-dir\\file1");
    DeleteFileA("test-dir\\file2");
    RemoveDirectoryA("test-dir\\dir1");
    RemoveDirectoryA("test-dir");
}