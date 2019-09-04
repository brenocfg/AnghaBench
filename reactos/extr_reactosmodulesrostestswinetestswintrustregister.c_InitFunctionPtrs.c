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

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pWintrustAddActionID ; 
 void* pWintrustAddDefaultForUsage ; 
 void* pWintrustGetRegPolicyFlags ; 
 void* pWintrustLoadFunctionPointers ; 
 void* pWintrustRemoveActionID ; 
 void* pWintrustSetRegPolicyFlags ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void InitFunctionPtrs(void)
{
    HMODULE hWintrust = GetModuleHandleA("wintrust.dll");

#define WINTRUST_GET_PROC(func) \
    p ## func = (void*)GetProcAddress(hWintrust, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    WINTRUST_GET_PROC(WintrustAddActionID)
    WINTRUST_GET_PROC(WintrustAddDefaultForUsage)
    WINTRUST_GET_PROC(WintrustGetRegPolicyFlags)
    WINTRUST_GET_PROC(WintrustLoadFunctionPointers)
    WINTRUST_GET_PROC(WintrustRemoveActionID)
    WINTRUST_GET_PROC(WintrustSetRegPolicyFlags)

#undef WINTRUST_GET_PROC
}