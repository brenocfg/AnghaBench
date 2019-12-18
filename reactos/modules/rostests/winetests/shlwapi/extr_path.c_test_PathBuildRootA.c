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
 char* PathBuildRootA (char*,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static void test_PathBuildRootA(void)
{
    LPSTR root;
    char path[10];
    char root_expected[26][4];
    char drive;
    int j;

    /* set up the expected paths */
    for (drive = 'A'; drive <= 'Z'; drive++)
        sprintf(root_expected[drive - 'A'], "%c:\\", drive);

    /* test the expected values */
    for (j = 0; j < 26; j++)
    {
        SetLastError(0xdeadbeef);
        lstrcpyA(path, "aaaaaaaaa");
        root = PathBuildRootA(path, j);
        ok(root == path, "Expected root == path, got %p\n", root);
        ok(!lstrcmpA(root, root_expected[j]), "Expected %s, got %s\n", root_expected[j], root);
        ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
    }

    /* test a negative drive number */
    SetLastError(0xdeadbeef);
    lstrcpyA(path, "aaaaaaaaa");
    root = PathBuildRootA(path, -1);
    ok(root == path, "Expected root == path, got %p\n", root);
    ok(!lstrcmpA(path, "aaaaaaaaa") || !path[0], /* Vista */
       "Expected aaaaaaaaa or empty string, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* test a drive number greater than 25 */
    SetLastError(0xdeadbeef);
    lstrcpyA(path, "aaaaaaaaa");
    root = PathBuildRootA(path, 26);
    ok(root == path, "Expected root == path, got %p\n", root);
    ok(!lstrcmpA(path, "aaaaaaaaa") || !path[0], /* Vista */
       "Expected aaaaaaaaa or empty string, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* length of path is less than 4 */
    SetLastError(0xdeadbeef);
    lstrcpyA(path, "aa");
    root = PathBuildRootA(path, 0);
    ok(root == path, "Expected root == path, got %p\n", root);
    ok(!lstrcmpA(path, "A:\\"), "Expected A:\\, got %s\n", path);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());

    /* path is NULL */
    SetLastError(0xdeadbeef);
    root = PathBuildRootA(NULL, 0);
    ok(root == NULL, "Expected root == NULL, got %p\n", root);
    ok(GetLastError() == 0xdeadbeef, "Expected 0xdeadbeef, got %d\n", GetLastError());
}