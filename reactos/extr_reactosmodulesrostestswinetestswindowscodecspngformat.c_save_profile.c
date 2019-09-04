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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int lstrlenW (char*) ; 

__attribute__((used)) static WCHAR *save_profile( BYTE *buffer, UINT size )
{
    static const WCHAR tstW[] = {'t','s','t',0};
    WCHAR path[MAX_PATH], filename[MAX_PATH], *ret;
    HANDLE handle;
    DWORD count;

    GetTempPathW(MAX_PATH, path);
    GetTempFileNameW(path, tstW, 0, filename);

    handle = CreateFileW(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (handle == INVALID_HANDLE_VALUE) return NULL;

    WriteFile(handle, buffer, size, &count, NULL);
    CloseHandle( handle );

    ret = HeapAlloc(GetProcessHeap(), 0, (lstrlenW(filename) + 1) * sizeof(WCHAR));
    lstrcpyW(ret, filename);
    return ret;
}