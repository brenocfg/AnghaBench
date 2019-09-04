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
typedef  int /*<<< orphan*/  data ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ *,char const*) ; 
 int SHKEY_Key_Classes ; 
 int SHKEY_Key_Explorer ; 
 int SHKEY_Root_HKCU ; 
 int SHKEY_Root_HKLM ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSHGetShellKey (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSKAllocValueW (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int*) ; 
 int /*<<< orphan*/  pSKDeleteValueW (int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSKGetValueW (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  pSKSetValueW (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_SHGetShellKey(void)
{
    static const WCHAR ShellFoldersW[] = { 'S','h','e','l','l',' ','F','o','l','d','e','r','s',0 };
    static const WCHAR WineTestW[] = { 'W','i','n','e','T','e','s','t',0 };

    DWORD *alloc_data, data, size;
    HKEY hkey;
    HRESULT hres;

    /* Vista+ limits SHKEY enumeration values */
    SetLastError(0xdeadbeef);
    hkey = pSHGetShellKey(SHKEY_Key_Explorer, ShellFoldersW, FALSE);
    if (hkey)
    {
        /* Tests not working on Vista+ */
        RegCloseKey(hkey);

        hkey = pSHGetShellKey(SHKEY_Root_HKLM|SHKEY_Key_Classes, NULL, FALSE);
        ok(hkey != NULL, "hkey = NULL\n");
        RegCloseKey(hkey);
    }

    hkey = pSHGetShellKey(SHKEY_Root_HKCU|SHKEY_Key_Explorer, ShellFoldersW, FALSE);
    ok(hkey != NULL, "hkey = NULL\n");
    RegCloseKey(hkey);

    hkey = pSHGetShellKey(SHKEY_Root_HKLM|SHKEY_Key_Explorer, ShellFoldersW, FALSE);
    ok(hkey != NULL, "hkey = NULL\n");
    RegCloseKey(hkey);

    hkey = pSHGetShellKey(SHKEY_Root_HKLM, WineTestW, FALSE);
    ok(hkey == NULL, "hkey != NULL\n");

    hkey = pSHGetShellKey(SHKEY_Root_HKLM, NULL, FALSE);
    ok(hkey != NULL, "Can't open key\n");
    ok(SUCCEEDED(RegDeleteKeyW(hkey, WineTestW)), "Can't delete key\n");
    RegCloseKey(hkey);

    hkey = pSHGetShellKey(SHKEY_Root_HKLM, WineTestW, TRUE);
    if (!hkey && GetLastError() == ERROR_ACCESS_DENIED)
    {
        skip("Not authorized to create keys\n");
        return;
    }
    ok(hkey != NULL, "Can't create key\n");
    RegCloseKey(hkey);

    size = sizeof(data);
    hres = pSKGetValueW(SHKEY_Root_HKLM, WineTestW, NULL, NULL, &data, &size);
    ok(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "hres = %x\n", hres);

    data = 1234;
    hres = pSKSetValueW(SHKEY_Root_HKLM, WineTestW, NULL, REG_DWORD, &data, sizeof(DWORD));
    ok(hres == S_OK, "hres = %x\n", hres);

    size = 1;
    hres = pSKGetValueW(SHKEY_Root_HKLM, WineTestW, NULL, NULL, NULL, &size);
    ok(hres == S_OK, "hres = %x\n", hres);
    ok(size == sizeof(DWORD), "size = %d\n", size);

    data = 0xdeadbeef;
    hres = pSKGetValueW(SHKEY_Root_HKLM, WineTestW, NULL, NULL, &data, &size);
    ok(hres == S_OK, "hres = %x\n", hres);
    ok(size == sizeof(DWORD), "size = %d\n", size);
    ok(data == 1234, "data = %d\n", data);

    hres = pSKAllocValueW(SHKEY_Root_HKLM, WineTestW, NULL, NULL, (void**)&alloc_data, &size);
    ok(hres == S_OK, "hres= %x\n", hres);
    ok(size == sizeof(DWORD), "size = %d\n", size);
    if (SUCCEEDED(hres))
    {
        ok(*alloc_data == 1234, "*alloc_data = %d\n", *alloc_data);
        LocalFree(alloc_data);
    }

    hres = pSKDeleteValueW(SHKEY_Root_HKLM, WineTestW, NULL);
    ok(hres == S_OK, "hres = %x\n", hres);

    hres = pSKDeleteValueW(SHKEY_Root_HKLM, WineTestW, NULL);
    ok(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "hres = %x\n", hres);

    hres = pSKGetValueW(SHKEY_Root_HKLM, WineTestW, NULL, NULL, &data, &size);
    ok(hres == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "hres = %x\n", hres);

    hkey = pSHGetShellKey(SHKEY_Root_HKLM, NULL, FALSE);
    ok(hkey != NULL, "Can't create key\n");
    ok(SUCCEEDED(RegDeleteKeyW(hkey, WineTestW)), "Can't delete key\n");
    RegCloseKey(hkey);
}