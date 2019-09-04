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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_BAD_PATHNAME ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SHCreateStreamOnFileA (char*,int,int /*<<< orphan*/ **) ; 
 int STGM_CONVERT ; 
 int STGM_CREATE ; 
 int STGM_DELETEONRELEASE ; 
 int STGM_FAILIFTHERE ; 
 int STGM_TRANSACTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_IStream_invalid_operations (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_stream_qi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_stream_read_write (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHCreateStreamOnFileA(DWORD mode, DWORD stgm)
{
    IStream * stream;
    HRESULT ret;
    ULONG refcount;
    char test_file[MAX_PATH];
    static const CHAR testA_txt[] = "\\testA.txt";

    trace("SHCreateStreamOnFileA: testing mode %d, STGM flags %08x\n", mode, stgm);

    /* Don't used a fixed path for the testA.txt file */
    GetTempPathA(MAX_PATH, test_file);
    lstrcatA(test_file, testA_txt);

    /* invalid arguments */

    stream = NULL;
    ret = SHCreateStreamOnFileA(NULL, mode | stgm, &stream);
    if (ret == E_INVALIDARG) /* Win98 SE */ {
        win_skip("Not supported\n");
        return;
    }

    ok(ret == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) /* NT */ ||
       ret == HRESULT_FROM_WIN32(ERROR_BAD_PATHNAME) /* 9x */,
       "SHCreateStreamOnFileA: expected HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) "
       "or HRESULT_FROM_WIN32(ERROR_BAD_PATHNAME), got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileA: expected a NULL IStream object, got %p\n", stream);

if (0) /* This test crashes on WinXP SP2 */
{
    ret = SHCreateStreamOnFileA(test_file, mode | stgm, NULL);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileA: expected E_INVALIDARG, got 0x%08x\n", ret);
}

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_CONVERT | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileA: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileA: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_DELETEONRELEASE | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileA: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileA: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_TRANSACTED | stgm, &stream);
    ok(ret == E_INVALIDARG, "SHCreateStreamOnFileA: expected E_INVALIDARG, got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileA: expected a NULL IStream object, got %p\n", stream);

    /* file does not exist */

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_FAILIFTHERE | stgm, &stream);
    ok(ret == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "SHCreateStreamOnFileA: expected HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), got 0x%08x\n", ret);
    ok(stream == NULL, "SHCreateStreamOnFileA: expected a NULL IStream object, got %p\n", stream);

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_CREATE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileA: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileA: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_stream_qi(stream);
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileA: expected 0, got %d\n", refcount);
    }

    /* NOTE: don't delete the file, as it will be used for the file exists tests. */

    /* file exists */

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_FAILIFTHERE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileA: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileA: expected a valid IStream object, got NULL\n");

    if (stream) {
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileA: expected 0, got %d\n", refcount);
    }

    stream = NULL;
    ret = SHCreateStreamOnFileA(test_file, mode | STGM_CREATE | stgm, &stream);
    ok(ret == S_OK, "SHCreateStreamOnFileA: expected S_OK, got 0x%08x\n", ret);
    ok(stream != NULL, "SHCreateStreamOnFileA: expected a valid IStream object, got NULL\n");

    if (stream) {
        BOOL delret;

        test_stream_read_write(stream, mode);
        test_IStream_invalid_operations(stream, mode);

        refcount = IStream_Release(stream);
        ok(refcount == 0, "SHCreateStreamOnFileA: expected 0, got %d\n", refcount);

        delret = DeleteFileA(test_file);
        ok(delret, "SHCreateStreamOnFileA: could not delete file '%s', got error %d\n",
           test_file, GetLastError());
    }
}