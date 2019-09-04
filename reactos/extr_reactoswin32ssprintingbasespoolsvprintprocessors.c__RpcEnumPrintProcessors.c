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
typedef  int /*<<< orphan*/  WINSPOOL_HANDLE ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  cbStructureSize; int /*<<< orphan*/  pInfo; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AlignRpcPtr (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ EnumPrintProcessorsW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  MarshallDownStructuresArray (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ PrintProcessorInfo1Marshalling ; 
 scalar_t__ RpcImpersonateClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcRevertToSelf () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UndoAlignRpcPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

DWORD
_RpcEnumPrintProcessors(WINSPOOL_HANDLE pName, WCHAR* pEnvironment, DWORD Level, BYTE* pPrintProcessorInfo, DWORD cbBuf, DWORD* pcbNeeded, DWORD* pcReturned)
{
    DWORD dwErrorCode;
    PBYTE pPrintProcessorInfoAligned;

    dwErrorCode = RpcImpersonateClient(NULL);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RpcImpersonateClient failed with error %lu!\n", dwErrorCode);
        return dwErrorCode;
    }

    pPrintProcessorInfoAligned = AlignRpcPtr(pPrintProcessorInfo, &cbBuf);

    if (EnumPrintProcessorsW(pName, pEnvironment, Level, pPrintProcessorInfoAligned, cbBuf, pcbNeeded, pcReturned))
    {
        // Replace absolute pointer addresses in the output by relative offsets.
        MarshallDownStructuresArray(pPrintProcessorInfoAligned, *pcReturned, PrintProcessorInfo1Marshalling.pInfo, PrintProcessorInfo1Marshalling.cbStructureSize, TRUE);
    }
    else
    {
        dwErrorCode = GetLastError();
    }

    RpcRevertToSelf();
    UndoAlignRpcPtr(pPrintProcessorInfo, pPrintProcessorInfoAligned, cbBuf, pcbNeeded);

    return dwErrorCode;
}