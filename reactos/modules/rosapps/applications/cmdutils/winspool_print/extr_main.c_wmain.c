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
typedef  int /*<<< orphan*/  docInfo ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {char* pDocName; } ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DOC_INFO_1W ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ClosePrinter (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndDocPrinter (scalar_t__) ; 
 int /*<<< orphan*/  EndPagePrinter (scalar_t__) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_FILE_SIZE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  OpenPrinterW (char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StartDocPrinterW (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartPagePrinter (scalar_t__) ; 
 int /*<<< orphan*/  Usage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WritePrinter (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 scalar_t__ min (int,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

int wmain(int argc, WCHAR* argv[])
{
    int ReturnValue = 1;
    DWORD dwFileSize;
    DWORD dwRead, dwWritten;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    HANDLE hPrinter = NULL;
    DOC_INFO_1W docInfo;
    BYTE Buffer[4096];

    if (argc <= 1)
    {
        Usage(argv[0]);
        return 0;
    }

    hFile = CreateFileW(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("CreateFileW failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    dwFileSize = GetFileSize(hFile, NULL);
    if (dwFileSize == INVALID_FILE_SIZE)
    {
        printf("File is too big, or GetFileSize failed; last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    if (!OpenPrinterW(L"Dummy Printer On LPT1", &hPrinter, NULL))
    {
        printf("OpenPrinterW failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    /* Print to a printer, with the "RAW" datatype (pDatatype == NULL or "RAW") */
    ZeroMemory(&docInfo, sizeof(docInfo));
    docInfo.pDocName = L"winspool_print";

    if (!StartDocPrinterW(hPrinter, 1, (LPBYTE)&docInfo))
    {
        printf("StartDocPrinterW failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    if (!StartPagePrinter(hPrinter))
    {
        printf("StartPagePrinter failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    while (dwFileSize > 0)
    {
        dwRead = min(sizeof(Buffer), dwFileSize);
        if (!ReadFile(hFile, Buffer, dwRead, &dwRead, NULL))
        {
            printf("ReadFile failed, last error is %lu!\n", GetLastError());
            goto Cleanup;
        }
        dwFileSize -= dwRead;

        if (!WritePrinter(hPrinter, Buffer, dwRead, &dwWritten))
        {
            printf("WritePrinter failed, last error is %lu!\n", GetLastError());
            goto Cleanup;
        }
    }

    if (!EndPagePrinter(hPrinter))
    {
        printf("EndPagePrinter failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    if (!EndDocPrinter(hPrinter))
    {
        printf("EndDocPrinter failed, last error is %lu!\n", GetLastError());
        goto Cleanup;
    }

    ReturnValue = 0;

Cleanup:
    if (hPrinter)
        ClosePrinter(hPrinter);

    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    return ReturnValue;
}