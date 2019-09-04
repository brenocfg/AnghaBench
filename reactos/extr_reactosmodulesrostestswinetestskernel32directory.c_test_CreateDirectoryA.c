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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_BAD_PATHNAME ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 scalar_t__ RemoveDirectoryA (char*) ; 
 scalar_t__ SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_CreateDirectoryA(void)
{
    char tmpdir[MAX_PATH];
    WCHAR curdir[MAX_PATH];
    BOOL ret;

    ret = CreateDirectoryA(NULL, NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_PATH_NOT_FOUND ||
                        GetLastError() == ERROR_INVALID_PARAMETER),
       "CreateDirectoryA(NULL): ret=%d err=%d\n", ret, GetLastError());

    ret = CreateDirectoryA("", NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_BAD_PATHNAME ||
                        GetLastError() == ERROR_PATH_NOT_FOUND),
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());

    ret = GetSystemDirectoryA(tmpdir, MAX_PATH);
    ok(ret < MAX_PATH, "System directory should fit into MAX_PATH\n");

    GetCurrentDirectoryW(MAX_PATH, curdir);
    ret = SetCurrentDirectoryA(tmpdir);
    ok(ret == TRUE, "could not chdir to the System directory\n");

    ret = CreateDirectoryA(".", NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());


    ret = CreateDirectoryA("..", NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());

    GetTempPathA(MAX_PATH, tmpdir);
    tmpdir[3] = 0; /* truncate the path */
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_ALREADY_EXISTS ||
                        GetLastError() == ERROR_ACCESS_DENIED),
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());

    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());


    lstrcatA(tmpdir, "?");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_INVALID_NAME ||
			GetLastError() == ERROR_PATH_NOT_FOUND),
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    RemoveDirectoryA(tmpdir);

    tmpdir[lstrlenA(tmpdir) - 1] = '*';
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_INVALID_NAME ||
			GetLastError() == ERROR_PATH_NOT_FOUND),
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    RemoveDirectoryA(tmpdir);

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me/Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND, 
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    RemoveDirectoryA(tmpdir);

    /* Test behavior with a trailing dot.
     * The directory should be created without the dot.
     */
    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me.");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,
       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    lstrcatA(tmpdir, "/Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,
       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    /* Test behavior with two trailing dots.
     * The directory should be created without the trailing dots.
     */
    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me..");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,
       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    lstrcatA(tmpdir, "/Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE || /* On Win98 */
       (ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND), /* On NT! */
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    if (ret == TRUE)
    {
        ret = RemoveDirectoryA(tmpdir);
        ok(ret == TRUE,
           "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());
    }

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    /* Test behavior with a trailing space.
     * The directory should be created without the trailing space.
     */
    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me ");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,
       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    lstrcatA(tmpdir, "/Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE || /* On Win98 */
       (ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND), /* On NT! */
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    if (ret == TRUE)
    {
        ret = RemoveDirectoryA(tmpdir);
        ok(ret == TRUE,
           "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());
    }

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    /* Test behavior with a trailing space.
     * The directory should be created without the trailing spaces.
     */
    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me  ");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE,
       "CreateDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());

    lstrcatA(tmpdir, "/Please Remove Me");
    ret = CreateDirectoryA(tmpdir, NULL);
    ok(ret == TRUE || /* On Win98 */
       (ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND), /* On NT! */
       "CreateDirectoryA(%s): ret=%d err=%d\n", tmpdir, ret, GetLastError());
    if (ret == TRUE)
    {
        ret = RemoveDirectoryA(tmpdir);
        ok(ret == TRUE,
           "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());
    }

    GetTempPathA(MAX_PATH, tmpdir);
    lstrcatA(tmpdir, "Please Remove Me");
    ret = RemoveDirectoryA(tmpdir);
    ok(ret == TRUE,
       "RemoveDirectoryA(%s) failed err=%d\n", tmpdir, GetLastError());
    SetCurrentDirectoryW(curdir);
}