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
typedef  scalar_t__ (* enum_handler_t ) (char*,char*,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetPrivateProfileSectionA (char*,char*,int,char*) ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKLM_DRIVERS32 ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fourcc_to_string (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static BOOL enum_drivers(DWORD fccType, enum_handler_t handler, void* param)
{
    char fccTypeStr[4];
    char name_buf[10];
    char buf[2048];

    DWORD i, cnt = 0, lRet;
    BOOL result = FALSE;
    HKEY hKey;

    fourcc_to_string(fccTypeStr, fccType);

    /* first, go through the registry entries */
    lRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, HKLM_DRIVERS32, 0, KEY_QUERY_VALUE, &hKey);
    if (lRet == ERROR_SUCCESS) 
    {
        i = 0;
        for (;;)
        {
            DWORD name_len = 10, driver_len = 128;
            lRet = RegEnumValueA(hKey, i++, name_buf, &name_len, 0, 0, (BYTE *)buf, &driver_len);
            if (lRet == ERROR_NO_MORE_ITEMS) break;
            if (name_len != 9 || name_buf[4] != '.') continue;
            if (fccType && strncasecmp(name_buf, fccTypeStr, 4)) continue;
            if ((result = handler(name_buf, buf, cnt++, param))) break;
        }
        RegCloseKey( hKey );
    }
    if (result) return result;

    /* if that didn't work, go through the values in system.ini */
    if (GetPrivateProfileSectionA("drivers32", buf, sizeof(buf), "system.ini")) 
    {
        char *s;
        for (s = buf; *s; s += strlen(s) + 1)
        {
            if (s[4] != '.' || s[9] != '=') continue;
            if (fccType && strncasecmp(s, fccTypeStr, 4)) continue;
            if ((result = handler(s, s + 10, cnt++, param))) break;
        }
    }

    return result;
}