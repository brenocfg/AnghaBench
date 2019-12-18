#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
struct TYPE_6__ {scalar_t__ hProcess; scalar_t__ hThread; } ;
struct TYPE_5__ {int cb; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manifest1 ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  winetest_get_mainargs (char***) ; 
 int /*<<< orphan*/  winetest_wait_child_process (scalar_t__) ; 

__attribute__((used)) static void run_child_process(void)
{
    char cmdline[MAX_PATH];
    char path[MAX_PATH];
    char **argv;
    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { 0 };
    HANDLE file;
    FILETIME now;
    BOOL ret;

    GetModuleFileNameA(NULL, path, MAX_PATH);
    strcat(path, ".manifest");
    if(!create_manifest_file(path, manifest1, -1, NULL, NULL)) {
        skip("Could not create manifest file\n");
        return;
    }

    si.cb = sizeof(si);
    winetest_get_mainargs( &argv );
    /* Vista+ seems to cache presence of .manifest files. Change last modified
       date to defeat the cache */
    file = CreateFileA(argv[0], FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE,
                       NULL, OPEN_EXISTING, 0, NULL);
    if (file != INVALID_HANDLE_VALUE) {
        GetSystemTimeAsFileTime(&now);
        SetFileTime(file, NULL, NULL, &now);
        CloseHandle(file);
    }
    sprintf(cmdline, "\"%s\" %s manifest1", argv[0], argv[1]);
    ret = CreateProcessA(argv[0], cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    ok(ret, "Could not create process: %u\n", GetLastError());
    winetest_wait_child_process( pi.hProcess );
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    DeleteFileA(path);
}