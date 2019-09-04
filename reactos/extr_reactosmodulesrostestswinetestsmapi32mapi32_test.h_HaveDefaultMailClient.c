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
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int TRUE ; 

__attribute__((used)) static BOOL HaveDefaultMailClient(void)
{
    HKEY Key;
    DWORD Type, Size;
    BYTE Buffer[64];
    BOOL HasHKCUKey;

    /* We check the default value of both HKCU\Software\Clients\Mail and
     * HKLM\Software\Clients\Mail, if one of them is present there is a default
     * mail client. If neither of these keys is present, we might be running
     * on an old Windows version (W95, NT4) and we assume a default mail client
     * might be available. Only if one of the keys is present, but there is
     * no default value do we assume there is no default client. */
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Clients\\Mail", 0, KEY_QUERY_VALUE, &Key) == ERROR_SUCCESS)
    {
        Size = sizeof(Buffer);
        /* Any return value besides ERROR_FILE_NOT_FOUND (including success,
           ERROR_MORE_DATA) indicates the value is present */
        if (RegQueryValueExA(Key, NULL, NULL, &Type, Buffer, &Size) != ERROR_FILE_NOT_FOUND)
        {
            RegCloseKey(Key);
            return TRUE;
        }
        RegCloseKey(Key);
        HasHKCUKey = TRUE;
    }
    else
        HasHKCUKey = FALSE;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Clients\\Mail", 0, KEY_QUERY_VALUE, &Key) == ERROR_SUCCESS)
    {
        Size = sizeof(Buffer);
        if (RegQueryValueExA(Key, NULL, NULL, &Type, Buffer, &Size) != ERROR_FILE_NOT_FOUND)
        {
            RegCloseKey(Key);
            return TRUE;
        }
        RegCloseKey(Key);
        return FALSE;
    }

    return ! HasHKCUKey;
}