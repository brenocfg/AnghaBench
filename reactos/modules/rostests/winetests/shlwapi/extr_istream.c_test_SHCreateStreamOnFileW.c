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
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int /*<<< orphan*/ * HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * IStream_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SHCreateStreamOnFileW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int STGM_CONVERT ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_FAILIFTHERE ; 
 int STGM_TRANSACTED ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_IStream_invalid_operations (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_stream_qi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_stream_read_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHCreateStreamOnFileW(DWORD mode, DWORD stgm)
{
    IStream * stream;
    HRESULT ret;
    ULONG refcount;
    WCHAR test_file[MAX_PATH];
    CHAR  test_fileA[MAX_PATH];
    static const CHAR testW_txt[] = "\\testW.txt";

    trace("SHCreateStreamOnFileW: testing mode %d, STGM flags %08x\n", mode, stgm);

    /* Don't used a fixed path for the testW.txt file */
    GetTempPathA(MAX_PATH, test_fileA);
    lstrcatA(test_fileA, testW_txt);
    MultiByteToWideChar(CP_ACP, 0, test_fileA, -1, test_file, MAX_PATH);

    /* invalid arguments */

    if (0)
    {
        /* Crashes on NT4 */
        stream = NULL;
        ret = SHCreateStreamOnFileW(NULL, mode | stgm, &stream);
        ok(ret == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) || /* XP */
           ret == E_INVALIDARG /* Vista */,
          "SHCreateStreamOnFileW: expected HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) or E_INVALIDARG, got 0x%08x\n", ret);
        ok(stream == NULL, "SHCreateStreamOnFileW: expected a NULL IStream object, got %p\n", stream);
    }

    if (0)
    {
        /* This test crashes on WinXP SP2 */
            ret = SHCreateStreamOnFileW(test_file, mode | stgm, NULL);
            ok(ret == E_INVALIDARG, "SHCreateStreamOnFileW: expected E_INVALIDARG, got 0x%08x\n", ret);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_CONVERT | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileW: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileW: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_DELETEONRELEASE | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileW: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileW: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_TRANSACTED | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileW: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileW: expected a NULL IStream object, got %p\n", stream);

    /* file does not exist */

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_FAILIFTHERE | stgm, &stream);
    if (ret == E_INVALIDARG) /* Win98 SE */ {
        win_skip("Not supported\n");
        return;
    }

    ok(ret == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "SHCreateStreamOnFileW: expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileW: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_CREATE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileW: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileW: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_stream_qi(stream);
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileW: expected 0, got %d\n", refcount);
    }

    /* NOTE: don't delete the file, as it will be used for the file exists tests. */

    /* file exists */

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_FAILIFTHERE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileW: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileW: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileW: expected 0, got %d\n", refcount);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileW(test_file, mode | STGM_CREATE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileW: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileW: expected a valid IStream object, got NULL\n");

    if (stream) {
        BOOL delret;

        test_stream_read_write(stream, mode);
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileW: expected 0, got %d\n", refcount);

        delret = DeleteFileA(test_fileA);
        ok(delret, "SHCreateStreamOnFileW: could not delete the test file, got error %d\n",
           GetLastError());
    }
}