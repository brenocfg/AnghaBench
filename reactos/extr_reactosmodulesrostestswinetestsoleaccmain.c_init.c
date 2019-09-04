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
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 void* pGetProcessHandleFromHwnd ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init(void)
{
    HMODULE oleacc = GetModuleHandleA("oleacc.dll");

    pGetProcessHandleFromHwnd = (void*)GetProcAddress(oleacc, "GetProcessHandleFromHwnd");
    if(!pGetProcessHandleFromHwnd) {
        win_skip("GetProcessHandleFromHwnd not available\n");
        return FALSE;
    }

    return TRUE;
}