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
typedef  int* PDWORD ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  LPCOMMCONFIG ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  COMMCONFIG ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetDefaultCommConfigW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int GetLastError () ; 

__attribute__((used)) static DWORD
_HandleGetDefaultCommConfig(PBYTE pInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded)
{
    // Sanity checks
    if (!pInputData || !pcbOutputNeeded)
        return ERROR_INVALID_PARAMETER;

    *pcbOutputNeeded = sizeof(COMMCONFIG);

    // Check if the supplied buffer is large enough.
    if (cbOutputData < *pcbOutputNeeded)
        return ERROR_INSUFFICIENT_BUFFER;

    // Finally get the port configuration.
    if (!GetDefaultCommConfigW((PCWSTR)pInputData, (LPCOMMCONFIG)pOutputData, pcbOutputNeeded))
        return GetLastError();

    return ERROR_SUCCESS;
}