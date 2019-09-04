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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  cbStructureSize; int /*<<< orphan*/  pInfo; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AlignRpcPtr (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetPrinterDriverW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  MarshallDownStructure (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RpcImpersonateClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcRevertToSelf () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UndoAlignRpcPtr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 TYPE_1__** pPrinterDriverMarshalling ; 

DWORD
_RpcGetPrinterDriver(WINSPOOL_PRINTER_HANDLE hPrinter, WCHAR* pEnvironment, DWORD Level, BYTE* pDriver, DWORD cbBuf, DWORD* pcbNeeded)
{
    DWORD dwErrorCode;
    PBYTE pDriverAligned;

    dwErrorCode = RpcImpersonateClient(NULL);
    if (dwErrorCode != ERROR_SUCCESS)
    {
        ERR("RpcImpersonateClient failed with error %lu!\n", dwErrorCode);
        return dwErrorCode;
    }

    pDriverAligned = AlignRpcPtr(pDriver, &cbBuf);

    if (GetPrinterDriverW(hPrinter, pEnvironment, Level, pDriverAligned, cbBuf, pcbNeeded))
    {
        // Replace relative offset addresses in the output by absolute pointers.
        ASSERT(Level >= 1 && Level <= 3);
        MarshallDownStructure(pDriverAligned, pPrinterDriverMarshalling[Level]->pInfo, pPrinterDriverMarshalling[Level]->cbStructureSize, TRUE);
    }
    else
    {
        dwErrorCode = GetLastError();
    }

    RpcRevertToSelf();
    UndoAlignRpcPtr(pDriver, pDriverAligned, cbBuf, pcbNeeded);

    return dwErrorCode;
}