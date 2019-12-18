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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int WriteFile (scalar_t__,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_script_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void run_script(const char *name, const char *script_data, size_t script_size, DWORD expected_exit_code)
{
    char file_name[MAX_PATH];
    const char *ext;
    HANDLE file;
    DWORD size;
    BOOL res;

    ext = strrchr(name, '.');
    ok(ext != NULL, "no script extension\n");
    if(!ext)
      return;

    sprintf(file_name, "test%s", ext);

    file = CreateFileA(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed: %u\n", GetLastError());
    if(file == INVALID_HANDLE_VALUE)
        return;

    res = WriteFile(file, script_data, script_size, &size, NULL);
    CloseHandle(file);
    ok(res, "Could not write to file: %u\n", GetLastError());
    if(!res)
        return;

    run_script_file(file_name, expected_exit_code);

    DeleteFileA(file_name);
}