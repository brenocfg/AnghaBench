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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int GetFileAttributesA (char*) ; 
 char* GetLastError () ; 
 int GetShortPathNameA (char*,char*,int) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetLongPathNameA (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_relative_path(void)
{
    char path[MAX_PATH], buf[MAX_PATH];
    HANDLE file;
    int ret;
    WCHAR curdir[MAX_PATH];

    if (!pGetLongPathNameA) return;

    GetCurrentDirectoryW(MAX_PATH, curdir);
    GetTempPathA(MAX_PATH, path);
    ret = SetCurrentDirectoryA(path);
    ok(ret, "SetCurrentDirectory error %d\n", GetLastError());

    ret = CreateDirectoryA("foo", NULL);
    ok(ret, "CreateDirectory error %d\n", GetLastError());
    file = CreateFileA("foo\\file", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
    ok(file != INVALID_HANDLE_VALUE, "failed to create temp file\n");
    CloseHandle(file);
    ret = CreateDirectoryA("bar", NULL);
    ok(ret, "CreateDirectory error %d\n", GetLastError());
    ret = SetCurrentDirectoryA("bar");
    ok(ret, "SetCurrentDirectory error %d\n", GetLastError());

    ret = GetFileAttributesA("..\\foo\\file");
    ok(ret != INVALID_FILE_ATTRIBUTES, "GetFileAttributes error %d\n", GetLastError());

    strcpy(buf, "deadbeef");
    ret = pGetLongPathNameA(".", buf, MAX_PATH);
    ok(ret, "GetLongPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "."), "expected ., got %s\n", buf);
    strcpy(buf, "deadbeef");
    ret = GetShortPathNameA(".", buf, MAX_PATH);
    ok(ret, "GetShortPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "."), "expected ., got %s\n", buf);

    strcpy(buf, "deadbeef");
    ret = pGetLongPathNameA("..", buf, MAX_PATH);
    ok(ret, "GetLongPathName error %d\n", GetLastError());
    ok(!strcmp(buf, ".."), "expected .., got %s\n", buf);
    strcpy(buf, "deadbeef");
    ret = GetShortPathNameA("..", buf, MAX_PATH);
    ok(ret, "GetShortPathName error %d\n", GetLastError());
    ok(!strcmp(buf, ".."), "expected .., got %s\n", buf);

    strcpy(buf, "deadbeef");
    ret = pGetLongPathNameA("..\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetLongPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "..\\foo\\file"), "expected ..\\foo\\file, got %s\n", buf);
    strcpy(buf, "deadbeef");
    ret = GetShortPathNameA("..\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetShortPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "..\\foo\\file"), "expected ..\\foo\\file, got %s\n", buf);

    strcpy(buf, "deadbeef");
    ret = pGetLongPathNameA(".\\..\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetLongPathName error %d\n", GetLastError());
    ok(!strcmp(buf, ".\\..\\foo\\file"), "expected .\\..\\foo\\file, got %s\n", buf);
    strcpy(buf, "deadbeef");
    ret = GetShortPathNameA(".\\..\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetShortPathName error %d\n", GetLastError());
    ok(!strcmp(buf, ".\\..\\foo\\file"), "expected .\\..\\foo\\file, got %s\n", buf);

    /* test double delimiters */
    strcpy(buf, "deadbeef");
    ret = pGetLongPathNameA("..\\\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetLongPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "..\\\\foo\\file"), "expected ..\\\\foo\\file, got %s\n", buf);
    strcpy(buf, "deadbeef");
    ret = GetShortPathNameA("..\\\\foo\\file", buf, MAX_PATH);
    ok(ret, "GetShortPathName error %d\n", GetLastError());
    ok(!strcmp(buf, "..\\\\foo\\file"), "expected ..\\\\foo\\file, got %s\n", buf);

    SetCurrentDirectoryA("..");
    DeleteFileA("foo\\file");
    RemoveDirectoryA("foo");
    RemoveDirectoryA("bar");
    SetCurrentDirectoryW(curdir);
}