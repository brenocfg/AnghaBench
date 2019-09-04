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
typedef  char* PWSTR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * HKEY_CURRENT_USER ; 
 int /*<<< orphan*/ * HKEY_LOCAL_MACHINE ; 
 int MAX_PATH ; 
 int PREFIX_LEN ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,char*,int,int*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  strip_quotes (char*,int*) ; 

__attribute__((used)) static void get_dest_dir(HINF hInf, PCWSTR pszSection, PWSTR pszBuffer, DWORD dwSize)
{
    INFCONTEXT context;
    WCHAR key[MAX_PATH + 2], value[MAX_PATH + 2];
    WCHAR prefix[PREFIX_LEN + 2];
    HKEY root, subkey = 0;
    DWORD size;

    static const WCHAR hklm[] = {'H','K','L','M',0};
    static const WCHAR hkcu[] = {'H','K','C','U',0};

    /* load the destination parameters */
    SetupFindFirstLineW(hInf, pszSection, NULL, &context);
    SetupGetStringFieldW(&context, 1, prefix, PREFIX_LEN + 2, &size);
    strip_quotes(prefix, &size);
    SetupGetStringFieldW(&context, 2, key, MAX_PATH + 2, &size);
    strip_quotes(key, &size);
    SetupGetStringFieldW(&context, 3, value, MAX_PATH + 2, &size);
    strip_quotes(value, &size);

    if (!lstrcmpW(prefix, hklm))
        root = HKEY_LOCAL_MACHINE;
    else if (!lstrcmpW(prefix, hkcu))
        root = HKEY_CURRENT_USER;
    else
        root = NULL;

    size = dwSize * sizeof(WCHAR);

    /* fallback to the default destination dir if reg fails */
    if (RegOpenKeyW(root, key, &subkey) ||
        RegQueryValueExW(subkey, value, NULL, NULL, (LPBYTE)pszBuffer, &size))
    {
        SetupGetStringFieldW(&context, 5, pszBuffer, dwSize, &size);
        strip_quotes(pszBuffer, &size);
    }

    if (subkey) RegCloseKey(subkey);
}