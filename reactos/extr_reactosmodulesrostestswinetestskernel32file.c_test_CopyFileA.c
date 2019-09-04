#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prefix ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int dwLowDateTime; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_1__ FILETIME ;
typedef  int DWORD ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ CompareFileTime (TYPE_1__*,TYPE_1__*) ; 
 void* CopyFileA (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateFileA (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateFileMappingW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DELETE ; 
 int DeleteFileA (char*) ; 
 int ERROR_FILE_EXISTS ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SHARING_VIOLATION ; 
 int ERROR_USER_MAPPED_FILE ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetFileSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GetLastError () ; 
 int GetTempFileNameA (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int GetTempPathA (int,char*) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PAGE_READONLY ; 
 void* ReadFile (int /*<<< orphan*/ *,char*,int,int*,int /*<<< orphan*/ *) ; 
 int SEC_COMMIT ; 
 int SetFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 void* WriteFile (int /*<<< orphan*/ *,char const*,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_CopyFileA(void)
{
    char temp_path[MAX_PATH];
    char source[MAX_PATH], dest[MAX_PATH];
    static const char prefix[] = "pfx";
    HANDLE hfile;
    HANDLE hmapfile;
    FILETIME ft1, ft2;
    char buf[10];
    DWORD ret;
    BOOL retok;

    ret = GetTempPathA(MAX_PATH, temp_path);
    ok(ret != 0, "GetTempPathA error %d\n", GetLastError());
    ok(ret < MAX_PATH, "temp path should fit into MAX_PATH\n");

    ret = GetTempFileNameA(temp_path, prefix, 0, source);
    ok(ret != 0, "GetTempFileNameA error %d\n", GetLastError());

    /* copying a file to itself must fail */
    retok = CopyFileA(source, source, FALSE);
    ok( !retok && (GetLastError() == ERROR_SHARING_VIOLATION || broken(GetLastError() == ERROR_FILE_EXISTS) /* Win 9x */),
        "copying a file to itself didn't fail (ret=%d, err=%d)\n", retok, GetLastError());

    /* make the source have not zero size */
    hfile = CreateFileA(source, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0 );
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file\n");
    retok = WriteFile(hfile, prefix, sizeof(prefix), &ret, NULL );
    ok( retok && ret == sizeof(prefix),
       "WriteFile error %d\n", GetLastError());
    ok(GetFileSize(hfile, NULL) == sizeof(prefix), "source file has wrong size\n");
    /* get the file time and change it to prove the difference */
    ret = GetFileTime(hfile, NULL, NULL, &ft1);
    ok( ret, "GetFileTime error %d\n", GetLastError());
    ft1.dwLowDateTime -= 600000000; /* 60 second */
    ret = SetFileTime(hfile, NULL, NULL, &ft1);
    ok( ret, "SetFileTime error %d\n", GetLastError());
    GetFileTime(hfile, NULL, NULL, &ft1);  /* get the actual time back */
    CloseHandle(hfile);

    ret = GetTempFileNameA(temp_path, prefix, 0, dest);
    ok(ret != 0, "GetTempFileNameA error %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = CopyFileA(source, dest, TRUE);
    ok(!ret && GetLastError() == ERROR_FILE_EXISTS,
       "CopyFileA: unexpected error %d\n", GetLastError());

    ret = CopyFileA(source, dest, FALSE);
    ok(ret, "CopyFileA: error %d\n", GetLastError());

    /* copying from a read-locked source fails */
    hfile = CreateFileA(source, GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(!retok && GetLastError() == ERROR_SHARING_VIOLATION,
        "copying from a read-locked file succeeded when it shouldn't have\n");
    /* in addition, the source is opened before the destination */
    retok = CopyFileA("25f99d3b-4ba4-4f66-88f5-2906886993cc", dest, FALSE);
    ok(!retok && GetLastError() == ERROR_FILE_NOT_FOUND,
        "copying from a file that doesn't exist failed in an unexpected way (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* copying from a r+w opened, r shared source succeeds */
    hfile = CreateFileA(source, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(retok,
        "copying from an r+w opened and r shared file failed (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* copying from a delete-locked source mostly succeeds */
    hfile = CreateFileA(source, DELETE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open source file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(retok || broken(!retok && GetLastError() == ERROR_SHARING_VIOLATION) /* NT, 2000, XP */,
        "copying from a delete-locked file failed (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* copying to a write-locked destination fails */
    hfile = CreateFileA(dest, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(!retok && GetLastError() == ERROR_SHARING_VIOLATION,
        "copying to a write-locked file didn't fail (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* copying to a r+w opened, w shared destination mostly succeeds */
    hfile = CreateFileA(dest, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(retok || broken(!retok && GetLastError() == ERROR_SHARING_VIOLATION) /* Win 9x */,
        "copying to a r+w opened and w shared file failed (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* copying to a delete-locked destination fails, even when the destination is delete-shared */
    hfile = CreateFileA(dest, DELETE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE || broken(GetLastError() == ERROR_INVALID_PARAMETER) /* Win 9x */,
        "failed to open destination file, error %d\n", GetLastError());
    if (hfile != INVALID_HANDLE_VALUE)
    {
        retok = CopyFileA(source, dest, FALSE);
        ok(!retok && GetLastError() == ERROR_SHARING_VIOLATION,
            "copying to a delete-locked shared file didn't fail (ret=%d, err=%d)\n", retok, GetLastError());
        CloseHandle(hfile);
    }

    /* copy to a file that's opened the way Wine opens the source */
    hfile = CreateFileA(dest, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file, error %d\n", GetLastError());
    retok = CopyFileA(source, dest, FALSE);
    ok(retok || broken(GetLastError() == ERROR_SHARING_VIOLATION) /* Win 9x */,
        "copying to a file opened the way Wine opens the source failed (ret=%d, err=%d)\n", retok, GetLastError());
    CloseHandle(hfile);

    /* make sure that destination has correct size */
    hfile = CreateFileA(dest, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file\n");
    ret = GetFileSize(hfile, NULL);
    ok(ret == sizeof(prefix), "destination file has wrong size %d\n", ret);

    /* make sure that destination has the same filetime */
    ret = GetFileTime(hfile, NULL, NULL, &ft2);
    ok( ret, "GetFileTime error %d\n", GetLastError());
    ok(CompareFileTime(&ft1, &ft2) == 0, "destination file has wrong filetime\n");

    SetLastError(0xdeadbeef);
    ret = CopyFileA(source, dest, FALSE);
    ok(!ret && GetLastError() == ERROR_SHARING_VIOLATION,
       "CopyFileA: ret = %d, unexpected error %d\n", ret, GetLastError());

    /* make sure that destination still has correct size */
    ret = GetFileSize(hfile, NULL);
    ok(ret == sizeof(prefix), "destination file has wrong size %d\n", ret);
    retok = ReadFile(hfile, buf, sizeof(buf), &ret, NULL);
    ok( retok && ret == sizeof(prefix),
       "ReadFile: error %d\n", GetLastError());
    ok(!memcmp(prefix, buf, sizeof(prefix)), "buffer contents mismatch\n");

    /* check error on copying over a mapped file that was opened with FILE_SHARE_READ */
    hmapfile = CreateFileMappingW(hfile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
    ok(hmapfile != NULL, "CreateFileMapping: error %d\n", GetLastError());

    ret = CopyFileA(source, dest, FALSE);
    ok(!ret && GetLastError() == ERROR_SHARING_VIOLATION,
       "CopyFileA with mapped dest file: expected ERROR_SHARING_VIOLATION, got %d\n", GetLastError());

    CloseHandle(hmapfile);
    CloseHandle(hfile);

    hfile = CreateFileA(dest, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
    ok(hfile != INVALID_HANDLE_VALUE, "failed to open destination file\n");

    /* check error on copying over a mapped file that was opened with FILE_SHARE_WRITE */
    hmapfile = CreateFileMappingW(hfile, NULL, PAGE_READONLY | SEC_COMMIT, 0, 0, NULL);
    ok(hmapfile != NULL, "CreateFileMapping: error %d\n", GetLastError());

    ret = CopyFileA(source, dest, FALSE);
    ok(!ret, "CopyFileA: expected failure\n");
    ok(GetLastError() == ERROR_USER_MAPPED_FILE ||
       broken(GetLastError() == ERROR_SHARING_VIOLATION), /* Win9x */
       "CopyFileA with mapped dest file: expected ERROR_USER_MAPPED_FILE, got %d\n", GetLastError());

    CloseHandle(hmapfile);
    CloseHandle(hfile);

    ret = DeleteFileA(source);
    ok(ret, "DeleteFileA: error %d\n", GetLastError());
    ret = DeleteFileA(dest);
    ok(ret, "DeleteFileA: error %d\n", GetLastError());
}