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
struct TYPE_5__ {int /*<<< orphan*/  pOutputFile; int /*<<< orphan*/  pDocName; int /*<<< orphan*/  pDatatype; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwszOutputFile; int /*<<< orphan*/  pwszDocumentName; int /*<<< orphan*/  pwszDatatype; int /*<<< orphan*/  pwszPrinterPort; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_1__* PWINPRINT_HANDLE ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  TYPE_2__ DOC_INFO_1W ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePrinter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DllAllocSplMem (int const) ; 
 int /*<<< orphan*/  DllFreeSplMem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,int,...) ; 
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  EndDocPrinter (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  OpenPrinterW (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ReadPrinter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int*) ; 
 int /*<<< orphan*/  StartDocPrinterW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WritePrinter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 

DWORD
PrintRawJob(PWINPRINT_HANDLE pHandle, PWSTR pwszPrinterAndJob)
{
    // Use a read buffer of 256 KB size like Windows does.
    const DWORD cbReadBuffer = 262144;

    BOOL bStartedDoc = FALSE;
    DOC_INFO_1W DocInfo1;
    DWORD cbRead;
    DWORD cbWritten;
    DWORD dwErrorCode;
    HANDLE hPrintJob;
    HANDLE hPrintMonitor = NULL;
    PBYTE pBuffer = NULL;

    // Open the spooled job to read from it.
    if (!OpenPrinterW(pwszPrinterAndJob, &hPrintJob, NULL))
    {
        dwErrorCode = GetLastError();
        ERR("OpenPrinterW failed for \"%S\" with error %lu!\n", pwszPrinterAndJob, GetLastError());
        goto Cleanup;
    }

    // Open a Print Monitor handle to write to it.
    if (!OpenPrinterW(pHandle->pwszPrinterPort, &hPrintMonitor, NULL))
    {
        dwErrorCode = GetLastError();
        ERR("OpenPrinterW failed for \"%S\" with error %lu!\n", pHandle->pwszPrinterPort, GetLastError());
        goto Cleanup;
    }

    // Fill the Document Information.
    DocInfo1.pDatatype = pHandle->pwszDatatype;
    DocInfo1.pDocName = pHandle->pwszDocumentName;
    DocInfo1.pOutputFile = pHandle->pwszOutputFile;

    // Tell the Print Monitor that we're starting a new document.
    if (!StartDocPrinterW(hPrintMonitor, 1, (PBYTE)&DocInfo1))
    {
        dwErrorCode = GetLastError();
        ERR("StartDocPrinterW failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    bStartedDoc = TRUE;

    // Allocate a read buffer on the heap. This would easily exceed the stack size.
    pBuffer = DllAllocSplMem(cbReadBuffer);
    if (!pBuffer)
    {
        dwErrorCode = ERROR_NOT_ENOUGH_MEMORY;
        ERR("DllAllocSplMem failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Loop as long as data is available.
    while (ReadPrinter(hPrintJob, pBuffer, cbReadBuffer, &cbRead) && cbRead)
    {
        // Write it to the Print Monitor.
        WritePrinter(hPrintMonitor, pBuffer, cbRead, &cbWritten);
    }

    dwErrorCode = ERROR_SUCCESS;

Cleanup:
    if (pBuffer)
        DllFreeSplMem(pBuffer);
    
    if (bStartedDoc)
        EndDocPrinter(hPrintMonitor);

    if (hPrintMonitor)
        ClosePrinter(hPrintMonitor);

    if (hPrintJob)
        ClosePrinter(hPrintJob);

    return dwErrorCode;
}