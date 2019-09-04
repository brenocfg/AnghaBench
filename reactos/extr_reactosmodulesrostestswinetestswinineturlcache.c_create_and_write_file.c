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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int WriteFile (scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_and_write_file(LPCSTR filename, void *data, DWORD len)
{
    HANDLE file;
    DWORD written;
    BOOL ret;

    file = CreateFileA(filename, GENERIC_WRITE,
                       FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFileA failed with error %d\n", GetLastError());

    ret = WriteFile(file, data, len, &written, NULL);
    ok(ret, "WriteFile failed with error %d\n", GetLastError());

    CloseHandle(file);
}