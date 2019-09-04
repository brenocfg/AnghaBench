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
typedef  char* LPSTR ;

/* Variables and functions */
 int GetLastError () ; 
 int LONG_LEN ; 
 int MAX_PATH ; 
 char* PathAddBackslashA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_PathAddBackslash(void)
{
    LPSTR str;
    char path[MAX_PATH];
    char too_long[LONG_LEN];

    /* try a NULL path */
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(NULL);
    ok(str == NULL, "Expected str == NULL, got %p\n", str);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try an empty path */
    path[0] = '\0';
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(path);
    ok(str == (path + lstrlenA(path)), "Expected str to point to end of path, got %p\n", str);
    ok(!path[0], "Expected empty string, got %i\n", lstrlenA(path));
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a relative path */
    lstrcpyA(path, "one\\two");
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(path);
    ok(str == (path + lstrlenA(path)), "Expected str to point to end of path, got %p\n", str);
    ok(!lstrcmpA(path, "one\\two\\"), "Expected one\\two\\, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try periods */
    lstrcpyA(path, "one\\..\\two");
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(path);
    ok(str == (path + lstrlenA(path)), "Expected str to point to end of path, got %p\n", str);
    ok(!lstrcmpA(path, "one\\..\\two\\"), "Expected one\\..\\two\\, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try just a space */
    lstrcpyA(path, " ");
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(path);
    ok(str == (path + lstrlenA(path)), "Expected str to point to end of path, got %p\n", str);
    ok(!lstrcmpA(path, " \\"), "Expected  \\, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* path already has backslash */
    lstrcpyA(path, "C:\\one\\");
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(path);
    ok(str == (path + lstrlenA(path)), "Expected str to point to end of path, got %p\n", str);
    ok(!lstrcmpA(path, "C:\\one\\"), "Expected C:\\one\\, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    memset(too_long, 'a', LONG_LEN);
    too_long[LONG_LEN - 1] = '\0';

    /* path is longer than MAX_PATH */
    SetLastError(0xdeadbeef);
    str = PathAddBackslashA(too_long);
    ok(str == NULL, "Expected str == NULL, got %p\n", str);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
}