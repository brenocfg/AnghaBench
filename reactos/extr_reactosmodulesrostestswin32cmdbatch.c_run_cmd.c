#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_9__ {scalar_t__ hProcess; scalar_t__ hThread; } ;
struct TYPE_8__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_7__ {int member_0; scalar_t__ hStdError; scalar_t__ hStdOutput; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__ PROCESS_INFORMATION ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  STARTF_USESTDHANDLES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static BOOL run_cmd(const char *cmd_data, DWORD cmd_size)
{
    SECURITY_ATTRIBUTES sa = {sizeof(sa), 0, TRUE};
    char command[] = "test.cmd";
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    HANDLE file,fileerr;
    DWORD size;
    BOOL bres;

    file = CreateFileA("test.cmd", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed\n");
    if(file == INVALID_HANDLE_VALUE)
        return FALSE;

    bres = WriteFile(file, cmd_data, cmd_size, &size, NULL);
    CloseHandle(file);
    ok(bres, "Could not write to file: %u\n", GetLastError());
    if(!bres)
        return FALSE;

    file = CreateFileA("test.out", GENERIC_WRITE, FILE_SHARE_WRITE|FILE_SHARE_READ, &sa, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed\n");
    if(file == INVALID_HANDLE_VALUE)
        return FALSE;

    fileerr = CreateFileA("test.err", GENERIC_WRITE, FILE_SHARE_WRITE|FILE_SHARE_READ, &sa, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
    ok(fileerr != INVALID_HANDLE_VALUE, "CreateFile stderr failed\n");
    if(fileerr == INVALID_HANDLE_VALUE)
        return FALSE;

    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = file;
    si.hStdError = fileerr;
    bres = CreateProcessA(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    ok(bres, "CreateProcess failed: %u\n", GetLastError());
    if(!bres) {
        DeleteFileA("test.out");
        return FALSE;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(file);
    CloseHandle(fileerr);
    DeleteFileA("test.cmd");
    return TRUE;
}