#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int cVersion; int /*<<< orphan*/  pDependentFiles; } ;
struct TYPE_7__ {TYPE_1__* pPrinter; } ;
struct TYPE_6__ {char* pwszPrinterDriver; } ;
typedef  TYPE_2__* PLOCAL_PRINTER_HANDLE ;
typedef  int* PDWORD ;
typedef  TYPE_3__* PDRIVER_INFO_3W ;
typedef  char* PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  DRIVER_INFO_3W ;

/* Variables and functions */
 int /*<<< orphan*/  PackStrings (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToMultiSz (int /*<<< orphan*/ ) ; 
 size_t _countof (char**) ; 
 int /*<<< orphan*/  dwDriverInfo3Offsets ; 
 int wcslen (char*) ; 
 char* wszCurrentEnvironment ; 

__attribute__((used)) static void
_LocalGetPrinterDriverLevel3(PLOCAL_PRINTER_HANDLE pHandle, PDRIVER_INFO_3W* ppDriverInfo, PBYTE* ppDriverInfoEnd, PDWORD pcbNeeded)
{
    DWORD n;
    PCWSTR pwszStrings[9];

    /* Clearly these things should not be hardcoded, so when it is needed, someone can add meaningfull values here */
    pwszStrings[0] = pHandle->pPrinter->pwszPrinterDriver;  // pName
    pwszStrings[1] = wszCurrentEnvironment;  // pEnvironment
    pwszStrings[2] = L"c:\\reactos\\system32\\localspl.dll";  // pDriverPath
    pwszStrings[3] = L"c:\\reactos\\system32\\localspl.dll";  // pDataFile
    pwszStrings[4] = L"c:\\reactos\\system32\\printui.dll";  // pConfigFile
    pwszStrings[5] = L"";  // pHelpFile
    pwszStrings[6] = L"localspl.dll|printui.dll|";  // pDependentFiles, | is separator and terminator!
    pwszStrings[7] = NULL;  // pMonitorName
    pwszStrings[8] = NULL;  // pDefaultDataType


    // Calculate the string lengths.
    if (!ppDriverInfo)
    {
        for (n = 0; n < _countof(pwszStrings); ++n)
        {
            if (pwszStrings[n])
            {
                *pcbNeeded += (wcslen(pwszStrings[n]) + 1) * sizeof(WCHAR);
            }
        }

        *pcbNeeded += sizeof(DRIVER_INFO_3W);
        return;
    }

    (*ppDriverInfo)->cVersion = 3;

    // Finally copy the structure and advance to the next one in the output buffer.
    *ppDriverInfoEnd = PackStrings(pwszStrings, (PBYTE)(*ppDriverInfo), dwDriverInfo3Offsets, *ppDriverInfoEnd);
    ToMultiSz((*ppDriverInfo)->pDependentFiles);
    (*ppDriverInfo)++;
}