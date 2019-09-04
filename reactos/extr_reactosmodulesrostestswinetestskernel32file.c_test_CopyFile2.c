#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prefix ;
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  buf ;
typedef  char WCHAR ;
struct TYPE_11__ {int dwSize; void* dwCopyFlags; } ;
struct TYPE_10__ {int dwLowDateTime; } ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_1__ FILETIME ;
typedef  int DWORD ;
typedef  TYPE_2__ COPYFILE2_EXTENDED_PARAMETERS ;

/* Variables and functions */
 void* COPY_FILE_FAIL_IF_EXISTS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ CompareFileTime (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * CreateFileMappingW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileW (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DELETE ; 
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 int ERROR_FILE_EXISTS ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_SHARING_VIOLATION ; 
 int ERROR_USER_MAPPED_FILE ; 
 TYPE_2__* FALSE ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetFileSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GetLastError () ; 
 int GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int GetTempPathW (int,char*) ; 
 int HRESULT_FROM_WIN32 (int) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PAGE_READONLY ; 
 int ReadFile (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ *) ; 
 int SEC_COMMIT ; 
 int S_OK ; 
 int SetFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int WriteFile (int /*<<< orphan*/ *,char const*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pCopyFile2 (char const*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_CopyFile2(void)
{
    static const WCHAR doesntexistW[] = {'d','o','e','s','n','t','e','x','i','s','t',0};
    static const WCHAR prefix[] = {'p','f','x',0};
    WCHAR source[MAX_PATH], dest[MAX_PATH], temp_path[MAX_PATH];
    COPYFILE2_EXTENDED_PARAMETERS params;
    HANDLE hfile, hmapfile;
    FILETIME ft1, ft2;
    DWORD ret, len;
    char buf[10];
    HRESULT hr;

    if (!pCopyFile2)
    {
        skip("CopyFile2 is not available\n");
        return;
    }

    ret = GetTempPathW(MAX_PATH, temp_path);
    ok(ret != 0, "GetTempPathW error %d\n", GetLastError());
    ok(ret < MAX_PATH, "temp path should fit into MAX_PATH\n");

    ret = GetTempFileNameW(temp_path, prefix, 0, source);
    ok(ret != 0, "GetTempFileNameW error %d\n", GetLastError());

    ret = GetTempFileNameW(temp_path, prefix, 0, dest);
    ok(ret != 0, "GetTempFileNameW error %d\n", GetLastError());

    /* fail if exists */
    memset(&params, 0, sizeof(params));
    params.dwSize = sizeof(params);
    params.dwCopyFlags = COPY_FILE_FAIL_IF_EXISTS;

    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_EXISTS), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_FILE_EXISTS, "CopyFile2: last error %d\n", GetLastError());

    /* don't fail if exists */
    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;

    hr = pCopyFile2(source, dest, &params);
    ok(hr == S_OK, "CopyFile2: error 0x%08x\n", hr);

    /* copying a file to itself must fail */
    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;

    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, source, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: copying a file to itself didn't fail, 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());

    /* make the source have not zero size */
    hfile = CreateFileW(source, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0 );
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file\n");
    ret = WriteFile(hfile, prefix, sizeof(prefix), &len, NULL );
    ok(ret && len == sizeof(prefix), "WriteFile error %d\n", GetLastError());
    ok(GetFileSize(hfile, NULL) == sizeof(prefix), "source file has wrong size\n");

    /* get the file time and change it to prove the difference */
    ret = GetFileTime(hfile, NULL, NULL, &ft1);
    ok(ret, "GetFileTime error %d\n", GetLastError());
    ft1.dwLowDateTime -= 600000000; /* 60 second */
    ret = SetFileTime(hfile, NULL, NULL, &ft1);
    ok(ret, "SetFileTime error %d\n", GetLastError());
    GetFileTime(hfile, NULL, NULL, &ft1);  /* get the actual time back */
    CloseHandle(hfile);

    ret = GetTempFileNameW(temp_path, prefix, 0, dest);
    ok(ret != 0, "GetTempFileNameA error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = COPY_FILE_FAIL_IF_EXISTS;

    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_EXISTS), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_FILE_EXISTS, "CopyFile2: last error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, &params);
    ok(ret, "CopyFile2: error 0x%08x\n", hr);

    /* copying from a read-locked source fails */
    hfile = CreateFileW(source, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());

    /* in addition, the source is opened before the destination */
    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(doesntexistW, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "got 0x%08x\n", hr);
    ok(GetLastError() == ERROR_FILE_NOT_FOUND, "CopyFile2: last error %d\n", GetLastError());
    CloseHandle(hfile);

    /* copying from a r+w opened, r shared source succeeds */
    hfile = CreateFileW(source, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, &params);
    ok(hr == S_OK, "failed 0x%08x\n", hr);
    CloseHandle(hfile);

    /* copying from a delete-locked source mostly succeeds */
    hfile = CreateFileW(source, DELETE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, &params);
    ok(hr == S_OK, "failed 0x%08x\n", hr);
    CloseHandle(hfile);

    /* copying to a write-locked destination fails */
    hfile = CreateFileW(dest, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, FALSE);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());
    CloseHandle(hfile);

    /* copying to a r+w opened, w shared destination mostly succeeds */
    hfile = CreateFileW(dest, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, FALSE);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    CloseHandle(hfile);

    /* copying to a delete-locked destination fails, even when the destination is delete-shared */
    hfile = CreateFileW(dest, DELETE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());
    CloseHandle(hfile);

    /* copy to a file that's opened the way Wine opens the source */
    hfile = CreateFileW(dest, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, &params);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    CloseHandle(hfile);

    /* make sure that destination has correct size */
    hfile = CreateFileW(dest, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file\n");
    ret = GetFileSize(hfile, NULL);
    ok(ret == sizeof(prefix), "destination file has wrong size %d\n", ret);

    /* make sure that destination has the same filetime */
    ret = GetFileTime(hfile, NULL, NULL, &ft2);
    ok(ret, "GetFileTime error %d\n", GetLastError());
    ok(CompareFileTime(&ft1, &ft2) == 0, "destination file has wrong filetime\n");

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());

    /* make sure that destination still has correct size */
    ret = GetFileSize(hfile, NULL);
    ok(ret == sizeof(prefix), "destination file has wrong size %d\n", ret);
    ret = ReadFile(hfile, buf, sizeof(buf), &len, NULL);
    ok(ret && len == sizeof(prefix), "ReadFile: error %d\n", GetLastError());
    ok(!memcmp(prefix, buf, sizeof(prefix)), "buffer contents mismatch\n");

    /* check error on copying over a mapped file that was opened with FILE_SHARE_READ */
    hmapfile = CreateFileMappingW(hfile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
    ok(hmapfile != NULL, "CreateFileMapping: error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    SetLastError(0xdeadbeef);
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_SHARING_VIOLATION), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_SHARING_VIOLATION, "CopyFile2: last error %d\n", GetLastError());

    CloseHandle(hmapfile);
    CloseHandle(hfile);

    hfile = CreateFileW(dest, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file\n");

    /* check error on copying over a mapped file that was opened with FILE_SHARE_WRITE */
    hmapfile = CreateFileMappingW(hfile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
    ok(hmapfile != NULL, "CreateFileMapping: error %d\n", GetLastError());

    params.dwSize = sizeof(params);
    params.dwCopyFlags = 0;
    hr = pCopyFile2(source, dest, &params);
    ok(hr == HRESULT_FROM_WIN32(ERROR_USER_MAPPED_FILE), "CopyFile2: unexpected error 0x%08x\n", hr);
    ok(GetLastError() == ERROR_USER_MAPPED_FILE, "CopyFile2: last error %d\n", GetLastError());

    CloseHandle(hmapfile);
    CloseHandle(hfile);

    DeleteFileW(source);
    DeleteFileW(dest);
}