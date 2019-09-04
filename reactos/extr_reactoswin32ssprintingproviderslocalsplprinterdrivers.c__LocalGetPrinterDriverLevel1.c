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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {TYPE_1__* pPrinter; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwszPrinterDriver; } ;
typedef  TYPE_2__* PLOCAL_PRINTER_HANDLE ;
typedef  int* PDWORD ;
typedef  scalar_t__ PDRIVER_INFO_1W ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  DRIVER_INFO_1W ;

/* Variables and functions */
 int /*<<< orphan*/  PackStrings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwDriverInfo1Offsets ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_LocalGetPrinterDriverLevel1(PLOCAL_PRINTER_HANDLE pHandle, PDRIVER_INFO_1W* ppDriverInfo, PBYTE* ppDriverInfoEnd, PDWORD pcbNeeded)
{
    DWORD n;
    PCWSTR pwszStrings[1];

    /* This value is only here to send something, I have not verified if it is actually correct */
    pwszStrings[0] = pHandle->pPrinter->pwszPrinterDriver;

    // Calculate the string lengths.
    if (!ppDriverInfo)
    {
        for (n = 0; n < _countof(pwszStrings); ++n)
        {
            *pcbNeeded += (wcslen(pwszStrings[n]) + 1) * sizeof(WCHAR);
        }

        *pcbNeeded += sizeof(DRIVER_INFO_1W);
        return;
    }


    // Finally copy the structure and advance to the next one in the output buffer.
    *ppDriverInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppDriverInfo), dwDriverInfo1Offsets, *ppDriverInfoEnd);
    (*ppDriverInfo)++;
}