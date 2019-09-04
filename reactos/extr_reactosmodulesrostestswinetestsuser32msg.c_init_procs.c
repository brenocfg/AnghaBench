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
 void* pGetAncestor ; 
 void* pGetCPInfoExA ; 
 void* pGetMenuInfo ; 
 void* pGetMonitorInfoA ; 
 void* pKillSystemTimer ; 
 void* pMonitorFromPoint ; 
 void* pNotifyWinEvent ; 
 void* pSetCoalescableTimer ; 
 void* pSetMenuInfo ; 
 void* pSetSystemTimer ; 
 void* pSetWinEventHook ; 
 void* pTrackMouseEvent ; 
 void* pUnhookWinEvent ; 
 void* pUpdateLayeredWindow ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_procs(void)
{
    HMODULE user32 = GetModuleHandleA("user32.dll");
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");

#define GET_PROC(dll, func) \
    p ## func = (void*)GetProcAddress(dll, #func); \
    if(!p ## func) { \
      trace("GetProcAddress(%s) failed\n", #func); \
    }

    GET_PROC(user32, GetAncestor)
    GET_PROC(user32, GetMenuInfo)
    GET_PROC(user32, NotifyWinEvent)
    GET_PROC(user32, SetMenuInfo)
    GET_PROC(user32, SetWinEventHook)
    GET_PROC(user32, TrackMouseEvent)
    GET_PROC(user32, UnhookWinEvent)
    GET_PROC(user32, GetMonitorInfoA)
    GET_PROC(user32, MonitorFromPoint)
    GET_PROC(user32, UpdateLayeredWindow)
    GET_PROC(user32, SetSystemTimer)
    GET_PROC(user32, KillSystemTimer)
    GET_PROC(user32, SetCoalescableTimer)

    GET_PROC(kernel32, GetCPInfoExA)

#undef GET_PROC
}