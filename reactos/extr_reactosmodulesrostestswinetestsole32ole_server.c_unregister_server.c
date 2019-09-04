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

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WineTestObject ; 
 int /*<<< orphan*/  DELETE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void unregister_server(void)
{
    static const WCHAR clsidW[] = {'C','L','S','I','D','\\',0};
    DWORD ret;
    HKEY root;
    WCHAR buf[39 + 6];

    lstrcpyW(buf, clsidW);
    StringFromGUID2(&CLSID_WineTestObject, buf + 6, 39);

    ret = RegCreateKeyExW(HKEY_CLASSES_ROOT, buf, 0, NULL, 0,
                          DELETE, NULL, &root, NULL);
    if (ret == ERROR_SUCCESS)
    {
        ret = RegDeleteKeyA(root, "InprocHandler32");
        ok(ret == ERROR_SUCCESS, "RegDeleteKey error %u\n", ret);
        ret = RegDeleteKeyA(root, "LocalServer32");
        ok(ret == ERROR_SUCCESS, "RegDeleteKey error %u\n", ret);
        ret = RegDeleteKeyA(root, "");
        ok(ret == ERROR_SUCCESS, "RegDeleteKey error %u\n", ret);
        RegCloseKey(root);
    }
}