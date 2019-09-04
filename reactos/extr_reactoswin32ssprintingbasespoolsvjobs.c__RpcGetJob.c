#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINSPOOL_PRINTER_HANDLE ;
struct TYPE_2__ {int /*<<< orphan*/  cbStructureSize; int /*<<< orphan*/  pInfo; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AlignRpcPtr (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetJobW (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MarshallDownStructure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RpcImpersonateClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcRevertToSelf () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UndoAlignRpcPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 TYPE_1__** pJobInfoMarshalling ; 

DWORD
_RpcGetJob(WINSPOOL_PRINTER_HANDLE hPrinter, DWORD JobId, DWORD Level, BYTE* pJob, DWORD cbBuf, DWORD* pcbNeeded)
{
    DWORD dwErrorCode;
    PBYTE pJobAligned;

    dwErrorCode = RpcImpersonateClient(NULL);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RpcImpersonateClient failed with error %lu!\n", dwErrorCode);
        return dwErrorCode;
    }

    pJobAligned = AlignRpcPtr(pJob, &cbBuf);

    if (GetJobW(hPrinter, JobId, Level, pJobAligned, cbBuf, pcbNeeded))
    {
        // Replace absolute pointer addresses in the output by relative offsets.
        ASSERT(Level >= 1 && Level <= 2);
        MarshallDownStructure(pJobAligned, pJobInfoMarshalling[Level]->pInfo, pJobInfoMarshalling[Level]->cbStructureSize, TRUE);
    }
    else
    {
        dwErrorCode = GetLastError();
    }

    RpcRevertToSelf();
    UndoAlignRpcPtr(pJob, pJobAligned, cbBuf, pcbNeeded);

    return dwErrorCode;
}