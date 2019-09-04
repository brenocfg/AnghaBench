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
typedef  int /*<<< orphan*/  substring2W ;
typedef  int /*<<< orphan*/  substring2A ;
typedef  int /*<<< orphan*/  string2W ;
typedef  int /*<<< orphan*/  string2A ;
typedef  int /*<<< orphan*/  string1W ;
typedef  int /*<<< orphan*/  string1A ;
typedef  int /*<<< orphan*/  emptyW ;
typedef  int /*<<< orphan*/  emptyA ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char BYTE ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NOACCESS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int REG_BINARY ; 
 int REG_DWORD ; 
 int REG_EXPAND_SZ ; 
 int REG_MULTI_SZ ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RegQueryValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int*) ; 
 int RegSetValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,int) ; 
 int RegSetValueExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char const*,int) ; 
 int RegSetValueExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,char const*,int) ; 
 int RegSetValueW (int /*<<< orphan*/ ,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  hkey_main ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 scalar_t__ pRegGetValueA ; 
 int pRegSetKeyValueW (int /*<<< orphan*/ ,char const*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  test_hkey_main_Value_A (char const*,char const*,int) ; 
 int /*<<< orphan*/  test_hkey_main_Value_W (char const*,char const*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_set_value(void)
{
    DWORD ret;

    static const WCHAR name1W[] =   {'C','l','e','a','n','S','i','n','g','l','e','S','t','r','i','n','g', 0};
    static const WCHAR name2W[] =   {'S','o','m','e','I','n','t','r','a','Z','e','r','o','e','d','S','t','r','i','n','g', 0};
    static const WCHAR emptyW[] = {0};
    static const WCHAR string1W[] = {'T','h','i','s','N','e','v','e','r','B','r','e','a','k','s', 0};
    static const WCHAR string2W[] = {'T','h','i','s', 0 ,'B','r','e','a','k','s', 0 , 0 ,'A', 0 , 0 , 0 , 'L','o','t', 0 , 0 , 0 , 0, 0};
    static const WCHAR substring2W[] = {'T','h','i','s',0};

    static const char name1A[] =   "CleanSingleString";
    static const char name2A[] =   "SomeIntraZeroedString";
    static const char emptyA[] = "";
    static const char string1A[] = "ThisNeverBreaks";
    static const char string2A[] = "This\0Breaks\0\0A\0\0\0Lot\0\0\0\0";
    static const char substring2A[] = "This";

    if (0)
    {
        /* Crashes on NT4, Windows 2000 and XP SP1 */
        ret = RegSetValueA(hkey_main, NULL, REG_SZ, NULL, 0);
        ok(ret == ERROR_INVALID_PARAMETER, "RegSetValueA should have failed with ERROR_INVALID_PARAMETER instead of %d\n", ret);
    }

    ret = RegSetValueA(hkey_main, NULL, REG_SZ, string1A, sizeof(string1A));
    ok(ret == ERROR_SUCCESS, "RegSetValueA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, string1A, sizeof(string1A));
    test_hkey_main_Value_W(NULL, string1W, sizeof(string1W));

    /* RegSetValueA ignores the size passed in */
    ret = RegSetValueA(hkey_main, NULL, REG_SZ, string1A, 4);
    ok(ret == ERROR_SUCCESS, "RegSetValueA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, string1A, sizeof(string1A));
    test_hkey_main_Value_W(NULL, string1W, sizeof(string1W));

    /* stops at first null */
    ret = RegSetValueA(hkey_main, NULL, REG_SZ, string2A, sizeof(string2A));
    ok(ret == ERROR_SUCCESS, "RegSetValueA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, substring2A, sizeof(substring2A));
    test_hkey_main_Value_W(NULL, substring2W, sizeof(substring2W));

    /* only REG_SZ is supported on NT*/
    ret = RegSetValueA(hkey_main, NULL, REG_BINARY, string2A, sizeof(string2A));
    ok(ret == ERROR_INVALID_PARAMETER, "got %d (expected ERROR_INVALID_PARAMETER)\n", ret);

    ret = RegSetValueA(hkey_main, NULL, REG_EXPAND_SZ, string2A, sizeof(string2A));
    ok(ret == ERROR_INVALID_PARAMETER, "got %d (expected ERROR_INVALID_PARAMETER)\n", ret);

    ret = RegSetValueA(hkey_main, NULL, REG_MULTI_SZ, string2A, sizeof(string2A));
    ok(ret == ERROR_INVALID_PARAMETER, "got %d (expected ERROR_INVALID_PARAMETER)\n", ret);

    /* Test RegSetValueExA with a 'zero-byte' string (as Office 2003 does).
     * Surprisingly enough we're supposed to get zero bytes out of it.
     */
    ret = RegSetValueExA(hkey_main, name1A, 0, REG_SZ, (const BYTE *)emptyA, 0);
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, NULL, 0);
    test_hkey_main_Value_W(name1W, NULL, 0);

    /* test RegSetValueExA with an empty string */
    ret = RegSetValueExA(hkey_main, name1A, 0, REG_SZ, (const BYTE *)emptyA, sizeof(emptyA));
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, emptyA, sizeof(emptyA));
    test_hkey_main_Value_W(name1W, emptyW, sizeof(emptyW));

    /* test RegSetValueExA with off-by-one size */
    ret = RegSetValueExA(hkey_main, name1A, 0, REG_SZ, (const BYTE *)string1A, sizeof(string1A)-sizeof(string1A[0]));
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, string1A, sizeof(string1A));
    test_hkey_main_Value_W(name1W, string1W, sizeof(string1W));

    /* test RegSetValueExA with normal string */
    ret = RegSetValueExA(hkey_main, name1A, 0, REG_SZ, (const BYTE *)string1A, sizeof(string1A));
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, string1A, sizeof(string1A));
    test_hkey_main_Value_W(name1W, string1W, sizeof(string1W));

    /* test RegSetValueExA with intrazeroed string */
    ret = RegSetValueExA(hkey_main, name2A, 0, REG_SZ, (const BYTE *)string2A, sizeof(string2A));
    ok(ret == ERROR_SUCCESS, "RegSetValueExA failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name2A, string2A, sizeof(string2A));
    test_hkey_main_Value_W(name2W, string2W, sizeof(string2W));

    if (0)
    {
        /* Crashes on NT4, Windows 2000 and XP SP1 */
        ret = RegSetValueW(hkey_main, NULL, REG_SZ, NULL, 0);
        ok(ret == ERROR_INVALID_PARAMETER, "RegSetValueW should have failed with ERROR_INVALID_PARAMETER instead of %d\n", ret);

        RegSetValueExA(hkey_main, name2A, 0, REG_SZ, (const BYTE *)1, 1);
        RegSetValueExA(hkey_main, name2A, 0, REG_DWORD, (const BYTE *)1, 1);
    }

    ret = RegSetValueW(hkey_main, NULL, REG_SZ, string1W, sizeof(string1W));
    ok(ret == ERROR_SUCCESS, "RegSetValueW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, string1A, sizeof(string1A));
    test_hkey_main_Value_W(NULL, string1W, sizeof(string1W));

    ret = RegSetValueW(hkey_main, name1W, REG_SZ, string1W, sizeof(string1W));
    ok(ret == ERROR_SUCCESS, "RegSetValueW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, string1A, sizeof(string1A));
    test_hkey_main_Value_W(name1W, string1W, sizeof(string1W));

    /* RegSetValueW ignores the size passed in */
    ret = RegSetValueW(hkey_main, NULL, REG_SZ, string1W, 4 * sizeof(string1W[0]));
    ok(ret == ERROR_SUCCESS, "RegSetValueW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, string1A, sizeof(string1A));
    test_hkey_main_Value_W(NULL, string1W, sizeof(string1W));

    /* stops at first null */
    ret = RegSetValueW(hkey_main, NULL, REG_SZ, string2W, sizeof(string2W));
    ok(ret == ERROR_SUCCESS, "RegSetValueW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(NULL, substring2A, sizeof(substring2A));
    test_hkey_main_Value_W(NULL, substring2W, sizeof(substring2W));

    /* only REG_SZ is supported */
    ret = RegSetValueW(hkey_main, NULL, REG_BINARY, string2W, sizeof(string2W));
    ok(ret == ERROR_INVALID_PARAMETER, "RegSetValueW should have returned ERROR_INVALID_PARAMETER instead of %d\n", ret);
    ret = RegSetValueW(hkey_main, NULL, REG_EXPAND_SZ, string2W, sizeof(string2W));
    ok(ret == ERROR_INVALID_PARAMETER, "RegSetValueW should have returned ERROR_INVALID_PARAMETER instead of %d\n", ret);
    ret = RegSetValueW(hkey_main, NULL, REG_MULTI_SZ, string2W, sizeof(string2W));
    ok(ret == ERROR_INVALID_PARAMETER, "RegSetValueW should have returned ERROR_INVALID_PARAMETER instead of %d\n", ret);

    /* test RegSetValueExW with off-by-one size */
    ret = RegSetValueExW(hkey_main, name1W, 0, REG_SZ, (const BYTE *)string1W, sizeof(string1W)-sizeof(string1W[0]));
    ok(ret == ERROR_SUCCESS, "RegSetValueExW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, string1A, sizeof(string1A));
    test_hkey_main_Value_W(name1W, string1W, sizeof(string1W));

    /* test RegSetValueExW with normal string */
    ret = RegSetValueExW(hkey_main, name1W, 0, REG_SZ, (const BYTE *)string1W, sizeof(string1W));
    ok(ret == ERROR_SUCCESS, "RegSetValueExW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name1A, string1A, sizeof(string1A));
    test_hkey_main_Value_W(name1W, string1W, sizeof(string1W));

    /* test RegSetValueExW with intrazeroed string */
    ret = RegSetValueExW(hkey_main, name2W, 0, REG_SZ, (const BYTE *)string2W, sizeof(string2W));
    ok(ret == ERROR_SUCCESS, "RegSetValueExW failed: %d, GLE=%d\n", ret, GetLastError());
    test_hkey_main_Value_A(name2A, string2A, sizeof(string2A));
    test_hkey_main_Value_W(name2W, string2W, sizeof(string2W));

    /* test RegSetValueExW with data = 1 */
    ret = RegSetValueExW(hkey_main, name2W, 0, REG_SZ, (const BYTE *)1, 1);
    ok(ret == ERROR_NOACCESS, "RegSetValueExW should have failed with ERROR_NOACCESS: %d, GLE=%d\n", ret, GetLastError());
    ret = RegSetValueExW(hkey_main, name2W, 0, REG_DWORD, (const BYTE *)1, 1);
    ok(ret == ERROR_NOACCESS, "RegSetValueExW should have failed with ERROR_NOACCESS: %d, GLE=%d\n", ret, GetLastError());

    if (pRegGetValueA) /* avoid a crash on Windows 2000 */
    {
        ret = RegSetValueExW(hkey_main, NULL, 0, REG_SZ, NULL, 4);
        ok(ret == ERROR_NOACCESS, "RegSetValueExW should have failed with ERROR_NOACCESS: %d, GLE=%d\n", ret, GetLastError());

        ret = RegSetValueExW(hkey_main, NULL, 0, REG_SZ, NULL, 0);
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);

        ret = RegSetValueExW(hkey_main, NULL, 0, REG_DWORD, NULL, 4);
        ok(ret == ERROR_NOACCESS, "RegSetValueExW should have failed with ERROR_NOACCESS: %d, GLE=%d\n", ret, GetLastError());

        ret = RegSetValueExW(hkey_main, NULL, 0, REG_DWORD, NULL, 0);
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    }

    /* RegSetKeyValue */
    if (!pRegSetKeyValueW)
        win_skip("RegSetKeyValue() is not supported.\n");
    else
    {
        static const WCHAR subkeyW[] = {'s','u','b','k','e','y',0};
        DWORD len, type;
        HKEY subkey;

        ret = pRegSetKeyValueW(hkey_main, NULL, name1W, REG_SZ, (const BYTE*)string2W, sizeof(string2W));
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);
        test_hkey_main_Value_A(name1A, string2A, sizeof(string2A));
        test_hkey_main_Value_W(name1W, string2W, sizeof(string2W));

        ret = pRegSetKeyValueW(hkey_main, subkeyW, name1W, REG_SZ, string1W, sizeof(string1W));
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);

        ret = RegOpenKeyExW(hkey_main, subkeyW, 0, KEY_QUERY_VALUE, &subkey);
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);
        type = len = 0;
        ret = RegQueryValueExW(subkey, name1W, 0, &type, NULL, &len);
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);
        ok(len == sizeof(string1W), "got %d\n", len);
        ok(type == REG_SZ, "got type %d\n", type);

        ret = pRegSetKeyValueW(hkey_main, subkeyW, name1W, REG_SZ, NULL, 0);
        ok(ret == ERROR_SUCCESS, "got %d\n", ret);

        ret = pRegSetKeyValueW(hkey_main, subkeyW, name1W, REG_SZ, NULL, 4);
        ok(ret == ERROR_NOACCESS, "got %d\n", ret);

        ret = pRegSetKeyValueW(hkey_main, subkeyW, name1W, REG_DWORD, NULL, 4);
        ok(ret == ERROR_NOACCESS, "got %d\n", ret);

        RegCloseKey(subkey);
    }
}