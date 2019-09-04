#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hFile; int /*<<< orphan*/  pwszPortName; int /*<<< orphan*/ * pwszMapping; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_1__* PLOCALMON_PORT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DDD_REMOVE_DEFINITION ; 
 int /*<<< orphan*/  DefineDosDeviceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DllFreeSplMem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DllFreeSplStr (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetPortNameWithoutColon (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ _GetNonspooledPortName (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_ClosePortHandles(PLOCALMON_PORT pPort)
{
    PWSTR pwszNonspooledPortName;
    PWSTR pwszPortNameWithoutColon;

    // A port is already fully closed if the file handle is invalid.
    if (pPort->hFile == INVALID_HANDLE_VALUE)
        return;

    // Close the file handle.
    CloseHandle(pPort->hFile);
    pPort->hFile = INVALID_HANDLE_VALUE;

    // A NONSPOOLED port was only created if pwszMapping contains the current port mapping.
    if (!pPort->pwszMapping)
        return;

    // Free the information about the current mapping.
    DllFreeSplStr(pPort->pwszMapping);
    pPort->pwszMapping = NULL;

    // Finally get the required strings and remove the DOS device definition for the NONSPOOLED port.
    if (GetPortNameWithoutColon(pPort->pwszPortName, &pwszPortNameWithoutColon) == ERROR_SUCCESS)
    {
        if (_GetNonspooledPortName(pwszPortNameWithoutColon, &pwszNonspooledPortName) == ERROR_SUCCESS)
        {
            DefineDosDeviceW(DDD_REMOVE_DEFINITION, pwszNonspooledPortName, NULL);
            DllFreeSplMem(pwszNonspooledPortName);
        }

        DllFreeSplMem(pwszPortNameWithoutColon);
    }
}