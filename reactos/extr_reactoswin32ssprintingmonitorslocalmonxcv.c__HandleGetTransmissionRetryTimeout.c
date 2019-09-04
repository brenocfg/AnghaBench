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
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int*,int) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int GetLPTTransmissionRetryTimeout () ; 

__attribute__((used)) static DWORD
_HandleGetTransmissionRetryTimeout(PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded)
{
    DWORD dwTimeout;

    // Sanity checks
    if (!pOutputData || !pcbOutputNeeded)
        return ERROR_INVALID_PARAMETER;

    *pcbOutputNeeded = sizeof(DWORD);

    // Check if the supplied buffer is large enough.
    if (cbOutputData < *pcbOutputNeeded)
        return ERROR_INSUFFICIENT_BUFFER;

    // Retrieve and copy the number.
    dwTimeout = GetLPTTransmissionRetryTimeout();
    CopyMemory(pOutputData, &dwTimeout, sizeof(DWORD));
    return ERROR_SUCCESS;
}