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
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,char const*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 char* malloc (scalar_t__) ; 

BOOL readRegValue(HKEY root, const char *subkey, const char *name, char **value)
{
    HKEY hKey;
    char *buf = NULL;
    BOOL ret = FALSE;
    LONG result = RegOpenKeyEx(root,
                               subkey,
                               0L,
                               // KEY_READ | KEY_WOW64_64KEY,
                               KEY_READ,
                               &hKey);
    if (result != ERROR_SUCCESS) {
        goto out;
    }

    DWORD len, type;
    result = RegQueryValueEx(hKey,
                             name,
                             NULL,  // reserved
                             &type, // type
                             NULL,  // data
                             &len); // size
    if (result != ERROR_SUCCESS || type != REG_SZ) {
        goto out;
    }

    buf = malloc (len + 1);
    buf[len] = 0;
    result = RegQueryValueEx(hKey,
                             name,
                             NULL,          // reserved
                             NULL,          // type
                             (LPBYTE) buf,  // data
                             &len);         // size
    if (result != ERROR_SUCCESS) {
        goto out;
    }

    *value = buf;
    ret = TRUE;

out:
    RegCloseKey(hKey);
    return ret;
}