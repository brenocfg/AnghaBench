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

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileMappingA (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 char* MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 

__attribute__((used)) static DWORD map_file(const char *file_name, const char **ret)
{
    HANDLE file, map;
    DWORD size;

    file = CreateFileA(file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
    ok(file != INVALID_HANDLE_VALUE, "CreateFile failed: %08x\n", GetLastError());
    if(file == INVALID_HANDLE_VALUE)
        return 0;

    size = GetFileSize(file, NULL);

    map = CreateFileMappingA(file, NULL, PAGE_READONLY, 0, 0, NULL);
    CloseHandle(file);
    ok(map != NULL, "CreateFileMappingA(%s) failed: %u\n", file_name, GetLastError());
    if(!map)
        return 0;

    *ret = MapViewOfFile(map, FILE_MAP_READ, 0, 0, 0);
    ok(*ret != NULL, "MapViewOfFile failed: %u\n", GetLastError());
    CloseHandle(map);
    if(!*ret)
        return 0;

    return size;
}