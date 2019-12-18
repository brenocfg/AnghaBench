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
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NORM_IGNORECASE ; 
 int SHGetNewLinkInfoA (char*,char*,char*,int*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  createTestFile (char*) ; 
 scalar_t__ lstrcmpiA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  set_curr_dir_path (char*,char*) ; 

__attribute__((used)) static void test_sh_new_link_info(void)
{
    BOOL ret, mustcopy=TRUE;
    CHAR linkto[MAX_PATH];
    CHAR destdir[MAX_PATH];
    CHAR result[MAX_PATH];
    CHAR result2[MAX_PATH];

    /* source file does not exist */
    set_curr_dir_path(linkto, "nosuchfile.txt\0");
    set_curr_dir_path(destdir, "testdir2\0");
    ret = SHGetNewLinkInfoA(linkto, destdir, result, &mustcopy, 0);
    ok(ret == FALSE ||
       broken(ret == lstrlenA(result) + 1), /* NT4 */
       "SHGetNewLinkInfoA succeeded\n");
    ok(mustcopy == FALSE, "mustcopy should be FALSE\n");

    /* dest dir does not exist */
    set_curr_dir_path(linkto, "test1.txt\0");
    set_curr_dir_path(destdir, "nosuchdir\0");
    ret = SHGetNewLinkInfoA(linkto, destdir, result, &mustcopy, 0);
    ok(ret == TRUE ||
       broken(ret == lstrlenA(result) + 1), /* NT4 */
       "SHGetNewLinkInfoA failed, err=%i\n", GetLastError());
    ok(mustcopy == FALSE, "mustcopy should be FALSE\n");

    /* source file exists */
    set_curr_dir_path(linkto, "test1.txt\0");
    set_curr_dir_path(destdir, "testdir2\0");
    ret = SHGetNewLinkInfoA(linkto, destdir, result, &mustcopy, 0);
    ok(ret == TRUE ||
       broken(ret == lstrlenA(result) + 1), /* NT4 */
       "SHGetNewLinkInfoA failed, err=%i\n", GetLastError());
    ok(mustcopy == FALSE, "mustcopy should be FALSE\n");
    ok(CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, destdir,
                      lstrlenA(destdir), result, lstrlenA(destdir)) == CSTR_EQUAL,
       "%s does not start with %s\n", result, destdir);
    ok(lstrlenA(result) > 4 && lstrcmpiA(result+lstrlenA(result)-4, ".lnk") == 0,
       "%s does not end with .lnk\n", result);

    /* preferred target name already exists */
    createTestFile(result);
    ret = SHGetNewLinkInfoA(linkto, destdir, result2, &mustcopy, 0);
    ok(ret == TRUE ||
       broken(ret == lstrlenA(result2) + 1), /* NT4 */
       "SHGetNewLinkInfoA failed, err=%i\n", GetLastError());
    ok(mustcopy == FALSE, "mustcopy should be FALSE\n");
    ok(CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, destdir,
                      lstrlenA(destdir), result2, lstrlenA(destdir)) == CSTR_EQUAL,
       "%s does not start with %s\n", result2, destdir);
    ok(lstrlenA(result2) > 4 && lstrcmpiA(result2+lstrlenA(result2)-4, ".lnk") == 0,
       "%s does not end with .lnk\n", result2);
    ok(lstrcmpiA(result, result2) != 0, "%s and %s are the same\n", result, result2);
    DeleteFileA(result);
}