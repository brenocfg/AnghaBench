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
typedef  scalar_t__ HANDLE ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTempFileNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int WriteFile (scalar_t__,unsigned char const*,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temp_path ; 

BOOL extract2(char* filename, const unsigned char* data, size_t len)
{
    HANDLE hFile;
    BOOL bRet;
    DWORD dwWritten;

    if (!GetTempFileNameA(temp_path, "mpa", 0, filename))
    {
        ok(0, "GetTempFileNameA failed %lu\n", GetLastError());
        return FALSE;
    }

    hFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        ok(0, "CreateFileA failed %lu\n", GetLastError());
        DeleteFileA(filename);
        return FALSE;
    }

    bRet = WriteFile(hFile, data, len, &dwWritten, NULL);
    CloseHandle(hFile);
    bRet = bRet && (dwWritten == len);

    if (!bRet)
    {
        ok(0, "WriteFile failed %lu\n", GetLastError());
        DeleteFileA(filename);
    }

    return bRet;
}