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
typedef  int /*<<< orphan*/  PRINTPROVIDOR ;
typedef  int /*<<< orphan*/  (* PInitializePrintProvidor ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  LPPRINTPROVIDOR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 

BOOL
GetLocalsplFuncs(LPPRINTPROVIDOR pp)
{
    HMODULE hLocalspl;
    PInitializePrintProvidor pfnInitializePrintProvidor;

    // Get us a handle to the loaded localspl.dll.
    hLocalspl = GetModuleHandleW(L"localspl");
    if (!hLocalspl)
    {
        skip("GetModuleHandleW failed with error %u!\n", GetLastError());
        return FALSE;
    }

    // Get a pointer to its InitializePrintProvidor function.
    pfnInitializePrintProvidor = (PInitializePrintProvidor)GetProcAddress(hLocalspl, "InitializePrintProvidor");
    if (!pfnInitializePrintProvidor)
    {
        skip("GetProcAddress failed with error %u!\n", GetLastError());
        return FALSE;
    }

    // Get localspl's function pointers.
    if (!pfnInitializePrintProvidor(pp, sizeof(PRINTPROVIDOR), NULL))
    {
        skip("pfnInitializePrintProvidor failed with error %u!\n", GetLastError());
        return FALSE;
    }

    return TRUE;
}