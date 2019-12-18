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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pRtlNtStatusToDosError ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strict ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int winetest_get_mainargs (char***) ; 

__attribute__((used)) static BOOL prepare_test(void)
{
    HMODULE ntdll;
    int argc;
    char** argv;

    ntdll = LoadLibraryA("ntdll.dll");
    pRtlNtStatusToDosError = (void*)GetProcAddress(ntdll, "RtlNtStatusToDosError");
    if (!pRtlNtStatusToDosError)
    {
        win_skip("RtlNtStatusToDosError is not available\n");
        return FALSE;
    }

    argc = winetest_get_mainargs(&argv);
    strict=(argc >= 3 && strcmp(argv[2],"strict")==0);
    return TRUE;
}