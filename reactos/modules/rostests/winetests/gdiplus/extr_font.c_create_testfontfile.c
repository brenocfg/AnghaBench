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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HRSRC ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FindResourceA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LoadResource (int /*<<< orphan*/ ,scalar_t__) ; 
 void* LockResource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 scalar_t__ RT_RCDATA ; 
 scalar_t__ SizeofResource (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,void*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_testfontfile(const WCHAR *filename, int resource, WCHAR pathW[MAX_PATH])
{
    DWORD written;
    HANDLE file;
    HRSRC res;
    void *ptr;

    GetTempPathW(MAX_PATH, pathW);
    lstrcatW(pathW, filename);

    file = CreateFileW(pathW, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok(file != INVALID_HANDLE_VALUE, "file creation failed, at %s, error %d\n", wine_dbgstr_w(pathW), GetLastError());

    res = FindResourceA(GetModuleHandleA(NULL), MAKEINTRESOURCEA(resource), (LPCSTR)RT_RCDATA);
    ok(res != 0, "couldn't find resource\n");
    ptr = LockResource(LoadResource(GetModuleHandleA(NULL), res));
    WriteFile(file, ptr, SizeofResource(GetModuleHandleA(NULL), res), &written, NULL);
    ok(written == SizeofResource(GetModuleHandleA(NULL), res), "couldn't write resource\n");
    CloseHandle(file);
}