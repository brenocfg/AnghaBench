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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SQLGetPrivateProfileString (char*,char*,char*,char*,int,char*) ; 
 int SQLWritePrivateProfileString (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  abcd_key ; 
 int /*<<< orphan*/  abcdini_key ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_SQLGetPrivateProfileString(void)
{
    int ret;
    char buffer[256] = {0};
    LONG reg_ret;

    strcpy(buffer, "wine");
    ret = SQLGetPrivateProfileString(NULL, "testing" , "default", buffer, 256, "ODBC.INI");
    ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, ""), "incorrect string '%s'\n", buffer);

    strcpy(buffer, "wine");
    ret = SQLGetPrivateProfileString("wineodbc", NULL , "default", buffer, 256, "ODBC.INI");
    ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, ""), "incorrect string '%s'\n", buffer);

    strcpy(buffer, "value");
    ret = SQLGetPrivateProfileString("wineodbc", "testing" , NULL, buffer, 256, "ODBC.INI");
    ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, ""), "incorrect string '%s'\n", buffer);

    ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultX", buffer, 256, "ODBC.INI");
    ok(ret == strlen("defaultX"), "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, "defaultX"), "incorrect string '%s'\n", buffer);

    ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultX", buffer, 4, "ODBC.INI");
    ok(ret == strlen("def"), "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, "def"), "incorrect string '%s'\n", buffer);

    ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultX", buffer, 8, "ODBC.INI");
    ok(ret == strlen("default"), "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, "default"), "incorrect string '%s'\n", buffer);

    ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultX", NULL, 256, "ODBC.INI");
    ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);

    strcpy(buffer, "value");
    ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultX", buffer, 0, "ODBC.INI");
    ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);
    ok(!strcmp(buffer, "value"), "incorrect string '%s'\n", buffer);

    ret = SQLWritePrivateProfileString("wineodbc", "testing" , "value0123456789", "abcd.ini");
    ok(ret, "SQLWritePrivateProfileString failed\n");
    if(ret)
    {
        HKEY hkey;

        ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultY", buffer, 256, "abcd.ini");
        ok(ret == strlen("value0123456789"), "SQLGetPrivateProfileString returned %d\n", ret);
        ok(!strcmp(buffer, "value0123456789"), "incorrect string '%s'\n", buffer);

        ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultY", NULL, 0, "abcd.ini");
        ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);

        ret = SQLGetPrivateProfileString("wineodbc", "testing" , "defaultY", buffer, 7, "abcd.ini");
        ok(ret == 6, "SQLGetPrivateProfileString returned %d\n", ret);

        strcpy(buffer, "wine");
        ret = SQLGetPrivateProfileString("wineodbc", NULL , "", buffer, 10, "abcd.ini");
        ok(ret == (strlen("testing")+1), "SQLGetPrivateProfileString returned %d\n", ret);
        ok(!strcmp(buffer, "testing"), "incorrect string '%s'\n", buffer);

        ret = SQLWritePrivateProfileString("wineodbc", "value" , "0", "abcd.ini");
        ok(ret, "SQLWritePrivateProfileString failed\n");

        strcpy(buffer, "wine");
        ret = SQLGetPrivateProfileString("wineodbc", NULL , "", buffer, 256, "abcd.ini");
        ok(ret == (strlen("testing") + strlen("value")+2), "SQLGetPrivateProfileString returned %d\n", ret);
        if(ret >= (strlen("testing") + strlen("value")+2))
        {
            ok(memcmp(buffer, "testing\0value\0", 14) == 0, "incorrect string '%s'\n", buffer);
        }

        strcpy(buffer, "XXXXXXXXXXXXXXX");
        ret = SQLGetPrivateProfileString("wineodbc", NULL , "", buffer, 10, "abcd.ini");
        ok(ret == (strlen("testing")+1), "SQLGetPrivateProfileString returned %d\n", ret);
        if(ret >= (strlen("testing")+1))
        {
            ok(!strcmp(buffer, "testing"), "incorrect string '%s'\n", buffer);
            /* Show that the buffer is cleared and partial enteries aren't added */
            ok(memcmp(buffer, "testing\0X", 9) != 0, "incorrect string '%s'\n", buffer);
        }

        strcpy(buffer, "wine");
        ret = SQLGetPrivateProfileString("wineodbc", NULL , "", buffer, 2, "abcd.ini");
        ok(ret == 0, "SQLGetPrivateProfileString returned %d\n", ret);

        reg_ret = RegOpenKeyExW(HKEY_CURRENT_USER, abcd_key, 0, KEY_READ, &hkey);
        ok(reg_ret == ERROR_SUCCESS, "RegOpenKeyExW failed\n");
        if(reg_ret == ERROR_SUCCESS)
        {
            reg_ret = RegDeleteKeyW(HKEY_CURRENT_USER, abcd_key);
            ok(reg_ret == ERROR_SUCCESS, "RegDeleteKeyW failed\n");

            RegCloseKey(hkey);
        }

        /* Cleanup key */
        reg_ret = RegDeleteKeyW(HKEY_CURRENT_USER, abcdini_key);
        ok(reg_ret == ERROR_SUCCESS, "RegDeleteKeyW failed\n");
    }
}