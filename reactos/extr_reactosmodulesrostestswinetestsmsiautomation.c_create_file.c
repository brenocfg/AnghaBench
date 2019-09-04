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
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetEndOfFile (scalar_t__) ; 
 int /*<<< orphan*/  SetFilePointer (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char const*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void create_file(const CHAR *name, DWORD size)
{
    HANDLE file;
    DWORD written, left;

    file = CreateFileA(name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    ok(file != INVALID_HANDLE_VALUE, "Failure to open file %s\n", name);
    WriteFile(file, name, strlen(name), &written, NULL);
    WriteFile(file, "\n", strlen("\n"), &written, NULL);

    left = size - lstrlenA(name) - 1;

    SetFilePointer(file, left, NULL, FILE_CURRENT);
    SetEndOfFile(file);

    CloseHandle(file);
}