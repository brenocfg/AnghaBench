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

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdll ; 
 void* pChangeDisplaySettingsExA ; 
 void* pChangeDisplaySettingsExW ; 
 void* pEnumDisplayDevicesA ; 
 void* pEnumDisplayMonitors ; 
 void* pGetDisplayConfigBufferSizes ; 
 void* pGetMonitorInfoA ; 
 void* pGetMonitorInfoW ; 
 void* pMonitorFromPoint ; 
 void* pMonitorFromRect ; 
 void* pMonitorFromWindow ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_function_pointers(void)
{
    hdll = GetModuleHandleA("user32.dll");

#define GET_PROC(func) \
    p ## func = (void*)GetProcAddress(hdll, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    GET_PROC(ChangeDisplaySettingsExA)
    GET_PROC(ChangeDisplaySettingsExW)
    GET_PROC(EnumDisplayDevicesA)
    GET_PROC(EnumDisplayMonitors)
    GET_PROC(GetDisplayConfigBufferSizes)
    GET_PROC(GetMonitorInfoA)
    GET_PROC(GetMonitorInfoW)
    GET_PROC(MonitorFromPoint)
    GET_PROC(MonitorFromRect)
    GET_PROC(MonitorFromWindow)

#undef GET_PROC
}