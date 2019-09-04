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
typedef  int /*<<< orphan*/  wszWinprintPath ;
typedef  char const WCHAR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_MOD_NOT_FOUND ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetPrintProcessorDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LoadLibraryW (char const*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  skip (char*,char const*,...) ; 
 int /*<<< orphan*/  wcscat (char const*,char*) ; 

PVOID
GetWinprintFunc(const char* FunctionName)
{
    DWORD cbNeeded;
    HMODULE hWinprint;
    PVOID pFunc;
    WCHAR wszWinprintPath[MAX_PATH];

    // Build the path to the default Print Processor winprint.dll in the Print Processor directory.
    if (!GetPrintProcessorDirectoryW(NULL, NULL, 1, (LPBYTE)wszWinprintPath, sizeof(wszWinprintPath), &cbNeeded))
    {
        skip("Could not determine the path to the Print Processor directory, last error is %lu!\n", GetLastError());
        return NULL;
    }

    wcscat(wszWinprintPath, L"\\winprint.dll");

    // Try loading it.
    hWinprint = LoadLibraryW(wszWinprintPath);
    if (!hWinprint)
    {
        if (GetLastError() != ERROR_MOD_NOT_FOUND)
        {
            skip("LoadLibraryW failed for %S with error %lu!\n", wszWinprintPath, GetLastError());
            return NULL;
        }

        // winprint.dll does not exist prior to NT6.
        // The default Print Processor is implemented in localspl.dll instead.
        hWinprint = LoadLibraryW(L"localspl.dll");
        if (!hWinprint)
        {
            skip("LoadLibraryW failed for localspl.dll with error %lu!\n", GetLastError());
            return NULL;
        }
    }

    // Get the function we are looking for.
    pFunc = GetProcAddress(hWinprint, FunctionName);
    if (!pFunc)
    {
        skip("GetProcAddress failed for %s with error %lu!\n", FunctionName, GetLastError());
        return NULL;
    }
    
    return pFunc;
}