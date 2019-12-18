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
typedef  float WCHAR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (float*) ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileW (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_DELETE_ON_CLOSE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,float*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  lstrcatW (float*,float const*) ; 
 int /*<<< orphan*/  lstrcmpW (float*,float*) ; 
 int /*<<< orphan*/  lstrcpyW (float*,float*) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pPathYetAnotherMakeUniqueName (float*,float*,float const*,float const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (float*) ; 

__attribute__((used)) static void test_PathYetAnotherMakeUniqueName(void)
{
    static const WCHAR shortW[] = {'f','i','l','e','.','t','s','t',0};
    static const WCHAR short2W[] = {'f','i','l','e',' ','(','2',')','.','t','s','t',0};
    static const WCHAR tmpW[] = {'t','m','p',0};
    static const WCHAR longW[] = {'n','a','m','e',0};
    static const WCHAR long2W[] = {'n','a','m','e',' ','(','2',')',0};
    WCHAR nameW[MAX_PATH], buffW[MAX_PATH], pathW[MAX_PATH];
    HANDLE file;
    BOOL ret;

    if (!pPathYetAnotherMakeUniqueName)
    {
        win_skip("PathYetAnotherMakeUniqueName() is not available.\n");
        return;
    }

if (0)
{
    /* crashes on Windows */
    ret = pPathYetAnotherMakeUniqueName(NULL, NULL, NULL, NULL);
    ok(!ret, "got %d\n", ret);

    ret = pPathYetAnotherMakeUniqueName(nameW, NULL, NULL, NULL);
    ok(!ret, "got %d\n", ret);
}

    GetTempPathW(ARRAY_SIZE(pathW), pathW);

    /* Using short name only first */
    nameW[0] = 0;
    ret = pPathYetAnotherMakeUniqueName(nameW, pathW, shortW, NULL);
    ok(ret, "got %d\n", ret);
    lstrcpyW(buffW, pathW);
    lstrcatW(buffW, shortW);
    ok(!lstrcmpW(nameW, buffW), "got %s, expected %s\n", wine_dbgstr_w(nameW), wine_dbgstr_w(buffW));

    /* now create a file with this name and get next name */
    file = CreateFileW(nameW, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);
    ok(file != NULL, "got %p\n", file);

    nameW[0] = 0;
    ret = pPathYetAnotherMakeUniqueName(nameW, pathW, shortW, NULL);
    ok(ret, "got %d\n", ret);
    lstrcpyW(buffW, pathW);
    lstrcatW(buffW, short2W);
    ok(!lstrcmpW(nameW, buffW), "got %s, expected %s\n", wine_dbgstr_w(nameW), wine_dbgstr_w(buffW));

    CloseHandle(file);

    /* Using short and long */
    nameW[0] = 0;
    ret = pPathYetAnotherMakeUniqueName(nameW, pathW, tmpW, longW);
    ok(ret, "got %d\n", ret);
    lstrcpyW(buffW, pathW);
    lstrcatW(buffW, longW);
    ok(!lstrcmpW(nameW, buffW), "got %s, expected %s\n", wine_dbgstr_w(nameW), wine_dbgstr_w(buffW));

    file = CreateFileW(nameW, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_DELETE_ON_CLOSE, NULL);
    ok(file != NULL, "got %p\n", file);

    nameW[0] = 0;
    ret = pPathYetAnotherMakeUniqueName(nameW, pathW, tmpW, longW);
    ok(ret, "got %d\n", ret);
    lstrcpyW(buffW, pathW);
    lstrcatW(buffW, long2W);
    ok(!lstrcmpW(nameW, buffW), "got %s, expected %s\n", wine_dbgstr_w(nameW), wine_dbgstr_w(buffW));

    CloseHandle(file);

    /* Using long only */
    nameW[0] = 0;
    ret = pPathYetAnotherMakeUniqueName(nameW, pathW, NULL, longW);
    ok(ret, "got %d\n", ret);
    lstrcpyW(buffW, pathW);
    lstrcatW(buffW, longW);
    ok(!lstrcmpW(nameW, buffW), "got %s, expected %s\n", wine_dbgstr_w(nameW), wine_dbgstr_w(buffW));
}