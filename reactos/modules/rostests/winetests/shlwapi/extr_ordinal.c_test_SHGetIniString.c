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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pSHGetIniStringW (char const*,char const*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp_wa (char*,char*) ; 
 int wine_dbgstr_w (char const*) ; 
 int /*<<< orphan*/  write_inifile (char*) ; 

__attribute__((used)) static void test_SHGetIniString(void)
{
    DWORD ret;
    WCHAR out[64] = {0};

    static const WCHAR TestAppW[] = {'T','e','s','t','A','p','p',0};
    static const WCHAR AKeyW[] = {'A','K','e','y',0};
    static const WCHAR AnotherKeyW[] = {'A','n','o','t','h','e','r','K','e','y',0};
    static const WCHAR JunkKeyW[] = {'J','u','n','k','K','e','y',0};
    static const WCHAR testpathW[] = {'C',':','\\','t','e','s','t','.','i','n','i',0};
    WCHAR pathW[MAX_PATH];

    lstrcpyW(pathW, testpathW);

    if (!write_inifile(pathW))
        return;

    if(0){
        /* these crash on Windows */
        pSHGetIniStringW(NULL, NULL, NULL, 0, NULL);
        pSHGetIniStringW(NULL, AKeyW, out, ARRAY_SIZE(out), pathW);
        pSHGetIniStringW(TestAppW, AKeyW, NULL, ARRAY_SIZE(out), pathW);
    }

    ret = pSHGetIniStringW(TestAppW, AKeyW, out, 0, pathW);
    ok(ret == 0, "SHGetIniStringW should have given 0, instead: %d\n", ret);

    /* valid arguments */
    out[0] = 0;
    SetLastError(0xdeadbeef);
    ret = pSHGetIniStringW(TestAppW, NULL, out, ARRAY_SIZE(out), pathW);
    ok(ret == 4, "SHGetIniStringW should have given 4, instead: %d\n", ret);
    ok(!lstrcmpW(out, AKeyW), "Expected %s, got: %s, %d\n",
                wine_dbgstr_w(AKeyW), wine_dbgstr_w(out), GetLastError());

    ret = pSHGetIniStringW(TestAppW, AKeyW, out, ARRAY_SIZE(out), pathW);
    ok(ret == 1, "SHGetIniStringW should have given 1, instead: %d\n", ret);
    ok(!strcmp_wa(out, "1"), "Expected L\"1\", got: %s\n", wine_dbgstr_w(out));

    ret = pSHGetIniStringW(TestAppW, AnotherKeyW, out, ARRAY_SIZE(out), pathW);
    ok(ret == 4, "SHGetIniStringW should have given 4, instead: %d\n", ret);
    ok(!strcmp_wa(out, "asdf"), "Expected L\"asdf\", got: %s\n", wine_dbgstr_w(out));

    out[0] = 1;
    ret = pSHGetIniStringW(TestAppW, JunkKeyW, out, ARRAY_SIZE(out), pathW);
    ok(ret == 0, "SHGetIniStringW should have given 0, instead: %d\n", ret);
    ok(*out == 0, "Expected L\"\", got: %s\n", wine_dbgstr_w(out));

    DeleteFileW(pathW);
}