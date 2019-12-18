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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_FILE_EXISTS ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int /*<<< orphan*/ * HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IStream_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SHCreateStreamOnFileEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int STGM_CREATE ; 
 int STGM_FAILIFTHERE ; 
 int STGM_READ ; 
 int STGM_TRANSACTED ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_IStream_invalid_operations (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_stream_qi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int winetest_debug ; 

__attribute__((used)) static void test_SHCreateStreamOnFileEx(DWORD mode, DWORD stgm)
{
    IStream * stream;
    IStream * template = NULL;
    HRESULT ret;
    ULONG refcount;
    WCHAR test_file[MAX_PATH];
    CHAR  test_fileA[MAX_PATH];
    static const CHAR testEx_txt[] = "\\testEx.txt";
    BOOL delret;

    if (winetest_debug > 1)
        trace("SHCreateStreamOnFileEx: testing mode %d, STGM flags %08x\n", mode, stgm);

    /* Don't used a fixed path for the testEx.txt file */
    GetTempPathA(MAX_PATH, test_fileA);
    lstrcatA(test_fileA, testEx_txt);
    MultiByteToWideChar(CP_ACP, 0, test_fileA, -1, test_file, MAX_PATH);

    /* invalid arguments */

    if (0)
    {
        /* Crashes on NT4 */
        stream = NULL;
        ret = SHCreateStreamOnFileEx(NULL, mode, 0, FALSE, NULL, &stream);
        ok(ret == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) || /* XP */
           ret == E_INVALIDARG /* Vista */,
          "SHCreateStreamOnFileEx: expected HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) or E_INVALIDARG, got 0x%08x\n", ret);
        ok(stream == NULL, "SHCreateStreamOnFileEx: expected a NULL IStream object, got %p\n", stream);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode, 0, FALSE, template, &stream);
    if (ret == HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED)) {
        win_skip("File probably locked by Anti-Virus/Spam software, trying again\n");
        Sleep(1000);
        ret = SHCreateStreamOnFileEx(test_file, mode, 0, FALSE, template, &stream);
    }
    ok( ret == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
        ret == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
        "SHCreateStreamOnFileEx: expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) or "
        "HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got 0x%08x\n", ret);

    ok(stream == NULL, "SHCreateStreamOnFileEx: expected a NULL IStream object, got %p\n", stream);

    if (0)
    {
        /* This test crashes on WinXP SP2 */
        ret = SHCreateStreamOnFileEx(test_file, mode, 0, FALSE, NULL, NULL);
        ok(ret == E_INVALIDARG, "SHCreateStreamOnFileEx: expected E_INVALIDARG, got 0x%08x\n", ret);
    }

    /* file does not exist */

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_FAILIFTHERE | stgm, 0, FALSE, NULL, &stream);
    if ((stgm & STGM_TRANSACTED) == STGM_TRANSACTED && mode == STGM_READ) {
        ok(ret == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) /* XP */ || ret == E_INVALIDARG /* Vista */,
          "SHCreateStreamOnFileEx: expected E_INVALIDARG or HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got 0x%08x\n", ret);

        if (ret == E_INVALIDARG) {
            skip("SHCreateStreamOnFileEx: STGM_TRANSACTED not supported in this configuration.\n");
            return;
        }
    } else {
        ok( ret == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
            ret == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER),
            "SHCreateStreamOnFileEx: expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) or "
            "HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER), got 0x%08x\n", ret);
    }
    ok(stream == NULL, "SHCreateStreamOnFileEx: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_FAILIFTHERE | stgm, 0, TRUE, NULL, &stream);
    /* not supported on win9x */
    if (broken(ret == HRESULT_FROM_WIN32(ERROR_INVALID_PARAMETER) && stream == NULL)) {
        skip("Not supported\n");
        DeleteFileA(test_fileA);
        return;
    }

    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_stream_qi(stream);
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);

        delret = DeleteFileA(test_fileA);
        ok(delret, "SHCreateStreamOnFileEx: could not delete the test file, got error %d\n",
           GetLastError());
    }

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, FALSE, NULL, &stream);
    if (ret == HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED)) {
        win_skip("File probably locked by Anti-Virus/Spam software, trying again\n");
        Sleep(1000);
        ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, FALSE, NULL, &stream);
    }
    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);

        delret = DeleteFileA(test_fileA);
        ok(delret, "SHCreateStreamOnFileEx: could not delete the test file, got error %d\n",
           GetLastError());
    }

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, TRUE, NULL, &stream);
    if (ret == HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED)) {
        win_skip("File probably locked by Anti-Virus/Spam software, trying again\n");
        Sleep(1000);
        ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, TRUE, NULL, &stream);
    }
    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);
    }

    /* NOTE: don't delete the file, as it will be used for the file exists tests. */

    /* file exists */

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_FAILIFTHERE | stgm, 0, FALSE, NULL, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_FAILIFTHERE | stgm, 0, TRUE, NULL, &stream);
    ok(ret == HRESULT_FROM_WIN32(ERROR_FILE_EXISTS), "SHCreateStreamOnFileEx: expected HRESULT_FROM_WIN32(ERROR_FILE_EXISTS), got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileEx: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, FALSE, NULL, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileEx(test_file, mode | STGM_CREATE | stgm, 0, TRUE, NULL, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileEx: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileEx: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileEx: expected 0, got %d\n", refcount);
    }

    delret = DeleteFileA(test_fileA);
    ok(delret, "SHCreateStreamOnFileEx: could not delete the test file, got error %d\n",
       GetLastError());
}