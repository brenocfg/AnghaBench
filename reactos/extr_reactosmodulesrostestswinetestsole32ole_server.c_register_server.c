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
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WineTestObject ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_READ ; 
 int KEY_WRITE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOL register_server(const char *server, BOOL inproc_handler)
{
    static const WCHAR clsidW[] = {'C','L','S','I','D','\\',0};
    DWORD ret;
    HKEY root;
    WCHAR buf[39 + 6];
    char server_path[MAX_PATH];

    lstrcpyA(server_path, server);
    lstrcatA(server_path, " ole_server");

    lstrcpyW(buf, clsidW);
    StringFromGUID2(&CLSID_WineTestObject, buf + 6, 39);

    ret = RegCreateKeyExW(HKEY_CLASSES_ROOT, buf, 0, NULL, 0,
                          KEY_READ | KEY_WRITE | KEY_CREATE_SUB_KEY, NULL, &root, NULL);
    if (ret == ERROR_SUCCESS)
    {
        ret = RegSetValueA(root, "LocalServer32", REG_SZ, server_path, strlen(server_path));
        ok(ret == ERROR_SUCCESS, "RegSetValue error %u\n", ret);

        if (inproc_handler)
        {
            ret = RegSetValueA(root, "InprocHandler32", REG_SZ, "ole32.dll", 9);
            ok(ret == ERROR_SUCCESS, "RegSetValue error %u\n", ret);
        }

        RegCloseKey(root);
    }

    return ret == ERROR_SUCCESS;
}