#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINSPOOL_PRINTER_HANDLE ;
struct TYPE_4__ {scalar_t__ Level1; } ;
struct TYPE_5__ {TYPE_1__ JobInfo; int /*<<< orphan*/  Level; } ;
typedef  TYPE_2__ WINSPOOL_JOB_CONTAINER ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ RpcImpersonateClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcRevertToSelf () ; 
 int /*<<< orphan*/  SetJobW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

DWORD
_RpcSetJob(WINSPOOL_PRINTER_HANDLE hPrinter, DWORD JobId, WINSPOOL_JOB_CONTAINER* pJobContainer, DWORD Command)
{
    DWORD dwErrorCode;

    dwErrorCode = RpcImpersonateClient(NULL);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RpcImpersonateClient failed with error %lu!\n", dwErrorCode);
        return dwErrorCode;
    }

    // pJobContainer->JobInfo is a union of pointers, so we can just convert any element to our BYTE pointer.
    if (!SetJobW(hPrinter, JobId, pJobContainer->Level, (PBYTE)pJobContainer->JobInfo.Level1, Command))
        dwErrorCode = GetLastError();

    RpcRevertToSelf();
    return dwErrorCode;
}