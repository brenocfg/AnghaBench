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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleW (char*) ; 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  skip (char*,int /*<<< orphan*/ ) ; 

PVOID
GetSpoolssFunc(const char* FunctionName)
{
    HMODULE hSpoolss;

    // Get us a handle to the loaded spoolss.dll.
    hSpoolss = GetModuleHandleW(L"spoolss");
    if (!hSpoolss)
    {
        skip("GetModuleHandleW failed with error %u!\n", GetLastError());
        return FALSE;
    }

    return GetProcAddress(hSpoolss, FunctionName);
}