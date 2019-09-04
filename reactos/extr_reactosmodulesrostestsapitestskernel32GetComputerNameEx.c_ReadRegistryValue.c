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
typedef  scalar_t__ PCHAR ;
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static
LSTATUS
ReadRegistryValue(PCHAR ValueName, PCHAR Value)
{
    INT ErrorCode;
    HKEY ParametersKey;
    DWORD RegType;
    DWORD RegSize = 0;

    /* Open the database path key */
    ErrorCode = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                              "System\\CurrentControlSet\\Services\\Tcpip\\Parameters",
                              0,
                              KEY_READ,
                              &ParametersKey);
    if (ErrorCode == NO_ERROR)
    {
        /* Read the actual path */
        ErrorCode = RegQueryValueExA(ParametersKey,
                                     ValueName,
                                     NULL,
                                     &RegType,
                                     NULL,
                                     &RegSize);
        if (RegSize)
        {
            /* Read the actual path */
            ErrorCode = RegQueryValueExA(ParametersKey,
                                         ValueName,
                                         NULL,
                                         &RegType,
                                         (LPBYTE)Value,
                                         &RegSize);
        }

        /* Close the key */
        RegCloseKey(ParametersKey);
    }
    return ErrorCode;
}