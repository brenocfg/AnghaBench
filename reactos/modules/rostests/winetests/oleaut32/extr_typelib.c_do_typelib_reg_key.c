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
typedef  int /*<<< orphan*/  typelibW ;
typedef  scalar_t__ WORD ;
typedef  char WCHAR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  KEY_WRITE ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ TRUE ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ myRegDeleteTreeW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static BOOL do_typelib_reg_key(GUID *uid, WORD maj, WORD min, DWORD arch, LPCWSTR base, BOOL remove)
{
    static const WCHAR typelibW[] = {'T','y','p','e','l','i','b','\\',0};
    static const WCHAR formatW[] = {'\\','%','u','.','%','u','\\','0','\\','w','i','n','%','u',0};
    static const WCHAR format2W[] = {'%','s','_','%','u','_','%','u','.','d','l','l',0};
    WCHAR buf[128];
    HKEY hkey;
    BOOL ret = TRUE;
    DWORD res;

    memcpy(buf, typelibW, sizeof(typelibW));
    StringFromGUID2(uid, buf + lstrlenW(buf), 40);

    if (remove)
    {
        ok(myRegDeleteTreeW(HKEY_CLASSES_ROOT, buf, 0) == ERROR_SUCCESS, "SHDeleteKey failed\n");
        return TRUE;
    }

    wsprintfW(buf + lstrlenW(buf), formatW, maj, min, arch);

    SetLastError(0xdeadbeef);
    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, buf, 0, NULL, 0,
                          KEY_WRITE, NULL, &hkey, NULL);
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("W-calls are not implemented\n");
        return FALSE;
    }

    if (res != ERROR_SUCCESS)
    {
        trace("RegCreateKeyExW failed: %u\n", res);
        return FALSE;
    }

    wsprintfW(buf, format2W, base, maj, min);
    if (RegSetValueExW(hkey, NULL, 0, REG_SZ,
                       (BYTE *)buf, (lstrlenW(buf) + 1) * sizeof(WCHAR)) != ERROR_SUCCESS)
    {
        trace("RegSetValueExW failed\n");
        ret = FALSE;
    }
    RegCloseKey(hkey);
    return ret;
}