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
 char* PathFindExtensionA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_PathFindExtensionA(void)
{
    LPSTR ext;
    char path[MAX_PATH];
    char too_long[LONG_LEN];

    /* try a NULL path */
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(NULL);
    ok(ext == NULL, "Expected NULL, got %p\n", ext);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try an empty path */
    path[0] = '\0';
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(path);
    ok(ext == path, "Expected ext == path, got %p\n", ext);
    ok(!ext[0], "Expected length 0, got %i\n", lstrlenA(ext));
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a path without an extension */
    lstrcpyA(path, "file");
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(path);
    ok(ext == path + lstrlenA(path), "Expected ext == path, got %p\n", ext);
    ok(!ext[0], "Expected length 0, got %i\n", lstrlenA(ext));
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a path with an extension */
    lstrcpyA(path, "file.txt");
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(path);
    ok(ext == path + lstrlenA("file"),
       "Expected ext == path + lstrlenA(\"file\"), got %p\n", ext);
    ok(!lstrcmpA(ext, ".txt"), "Expected .txt, got %s\n", ext);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a path with two extensions */
    lstrcpyA(path, "file.txt.doc");
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(path);
    ok(ext == path + lstrlenA("file.txt"),
       "Expected ext == path + lstrlenA(\"file.txt\"), got %p\n", ext);
    ok(!lstrcmpA(ext, ".doc"), "Expected .txt, got %s\n", ext);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a path longer than MAX_PATH without an extension*/
    memset(too_long, 'a', LONG_LEN);
    too_long[LONG_LEN - 1] = '\0';
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(too_long);
    ok(ext == too_long + LONG_LEN - 1, "Expected ext == too_long + LONG_LEN - 1, got %p\n", ext);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* try a path longer than MAX_PATH with an extension*/
    memset(too_long, 'a', LONG_LEN);
    too_long[LONG_LEN - 1] = '\0';
    lstrcpyA(too_long + 300, ".abcde");
    too_long[lstrlenA(too_long)] = 'a';
    SetLastError(0xdeadbeef);
    ext = PathFindExtensionA(too_long);
    ok(ext == too_long + 300, "Expected ext == too_long + 300, got %p\n", ext);
    ok(lstrlenA(ext) == LONG_LEN - 301, "Expected LONG_LEN - 301, got %i\n", lstrlenA(ext));
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
}