#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_5__ {int InternalHigh; scalar_t__ Internal; int /*<<< orphan*/  hEvent; } ;
struct TYPE_4__ {scalar_t__ NextEntryOffset; scalar_t__ Action; int FileNameLength; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__* PFILE_NOTIFY_INFORMATION ;
typedef  TYPE_2__ OVERLAPPED ;
typedef  scalar_t__ NTSTATUS ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int CloseHandle (scalar_t__) ; 
 scalar_t__ CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ DeleteFileW (char*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ FILE_ACTION_ADDED ; 
 int FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_FLAG_OVERLAPPED ; 
 int FILE_LIST_DIRECTORY ; 
 int FILE_NOTIFY_CHANGE_FILE_NAME ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTempPathW (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ RemoveDirectoryW (char*) ; 
 scalar_t__ STATUS_SUCCESS ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pReadDirectoryChangesW (scalar_t__,char*,int,scalar_t__,int,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_readdirectorychanges_filedir(void)
{
    NTSTATUS r;
    HANDLE hdir, hfile;
    char buffer[0x1000];
    DWORD fflags, filter = 0;
    OVERLAPPED ov;
    WCHAR path[MAX_PATH], subdir[MAX_PATH], file[MAX_PATH];
    static const WCHAR szBoo[] = { '\\','b','o','o',0 };
    static const WCHAR szHoo[] = { '\\','h','o','o',0 };
    static const WCHAR szFoo[] = { '\\','f','o','o',0 };
    PFILE_NOTIFY_INFORMATION pfni;

    SetLastError(0xdeadbeef);
    r = GetTempPathW( MAX_PATH, path );
    if (!r && (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED))
    {
        win_skip("GetTempPathW is not implemented\n");
        return;
    }
    ok( r != 0, "temp path failed\n");
    if (!r)
        return;

    lstrcatW( path, szBoo );
    lstrcpyW( subdir, path );
    lstrcatW( subdir, szHoo );

    lstrcpyW( file, path );
    lstrcatW( file, szFoo );

    DeleteFileW( file );
    RemoveDirectoryW( subdir );
    RemoveDirectoryW( path );

    r = CreateDirectoryW(path, NULL);
    ok( r == TRUE, "failed to create directory\n");

    fflags = FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED;
    hdir = CreateFileW(path, GENERIC_READ|SYNCHRONIZE|FILE_LIST_DIRECTORY, 
                        FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, 
                        OPEN_EXISTING, fflags, NULL);
    ok( hdir != INVALID_HANDLE_VALUE, "failed to open directory\n");

    ov.hEvent = CreateEventW( NULL, 0, 0, NULL );

    filter = FILE_NOTIFY_CHANGE_FILE_NAME;

    r = pReadDirectoryChangesW(hdir,buffer,sizeof buffer,TRUE,filter,NULL,&ov,NULL);
    ok(r==TRUE, "should return true\n");

    r = WaitForSingleObject( ov.hEvent, 10 );
    ok( r == WAIT_TIMEOUT, "should timeout\n" );

    r = CreateDirectoryW( subdir, NULL );
    ok( r == TRUE, "failed to create directory\n");

    hfile = CreateFileW( file, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL );
    ok( hfile != INVALID_HANDLE_VALUE, "failed to create file\n");
    ok( CloseHandle(hfile), "failed to close file\n");

    r = WaitForSingleObject( ov.hEvent, 1000 );
    ok( r == WAIT_OBJECT_0, "event should be ready\n" );

    ok( (NTSTATUS)ov.Internal == STATUS_SUCCESS, "ov.Internal wrong\n");
    ok( ov.InternalHigh == 0x12, "ov.InternalHigh wrong\n");

    pfni = (PFILE_NOTIFY_INFORMATION) buffer;
    ok( pfni->NextEntryOffset == 0, "offset wrong\n" );
    ok( pfni->Action == FILE_ACTION_ADDED, "action wrong\n" );
    ok( pfni->FileNameLength == 6, "len wrong\n" );
    ok( !memcmp(pfni->FileName,&szFoo[1],6), "name wrong\n" );

    r = DeleteFileW( file );
    ok( r == TRUE, "failed to delete file\n");

    r = RemoveDirectoryW( subdir );
    ok( r == TRUE, "failed to remove directory\n");

    CloseHandle(hdir);

    r = RemoveDirectoryW( path );
    ok( r == TRUE, "failed to remove directory\n");
}