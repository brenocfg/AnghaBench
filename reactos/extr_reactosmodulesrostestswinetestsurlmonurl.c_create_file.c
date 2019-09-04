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
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char const*) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  set_file_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char const* test_file ; 

__attribute__((used)) static void create_file(const char *file_name, const char *content)
{
    HANDLE file;
    DWORD size;
    CHAR path[MAX_PATH];

    file = CreateFileA(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed\n");
    if(file == INVALID_HANDLE_VALUE)
        return;

    if(test_file)
        DeleteFileA(test_file);
    test_file = file_name;
    WriteFile(file, content, strlen(content), &size, NULL);
    CloseHandle(file);

    GetCurrentDirectoryA(MAX_PATH, path);
    lstrcatA(path, "\\");
    lstrcatA(path, file_name);
    set_file_url(path);
}