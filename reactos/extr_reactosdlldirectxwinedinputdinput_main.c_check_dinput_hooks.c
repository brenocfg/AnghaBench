#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int dwCoopLevel; } ;
typedef  int /*<<< orphan*/  LPDIRECTINPUTDEVICE8W ;
typedef  TYPE_1__ IDirectInputDeviceImpl ;
typedef  int /*<<< orphan*/ * HHOOK ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DINPUT_instance ; 
 int DISCL_FOREGROUND ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostThreadMessageW (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SetWindowsHookExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnhookWindowsHookEx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WH_CALLWNDPROC ; 
 scalar_t__ WM_USER ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callwndproc_proc ; 
 int /*<<< orphan*/  dinput_hook_crit ; 
 int /*<<< orphan*/ * hook_thread_event ; 
 int /*<<< orphan*/  hook_thread_id ; 
 TYPE_1__* impl_from_IDirectInputDevice8W (int /*<<< orphan*/ ) ; 

void check_dinput_hooks(LPDIRECTINPUTDEVICE8W iface, BOOL acquired)
{
    static HHOOK callwndproc_hook;
    static ULONG foreground_cnt;
    IDirectInputDeviceImpl *dev = impl_from_IDirectInputDevice8W(iface);

    EnterCriticalSection(&dinput_hook_crit);

    if (dev->dwCoopLevel & DISCL_FOREGROUND)
    {
        if (acquired)
            foreground_cnt++;
        else
            foreground_cnt--;
    }

    if (foreground_cnt && !callwndproc_hook)
        callwndproc_hook = SetWindowsHookExW( WH_CALLWNDPROC, callwndproc_proc,
                                              DINPUT_instance, GetCurrentThreadId() );
    else if (!foreground_cnt && callwndproc_hook)
    {
        UnhookWindowsHookEx( callwndproc_hook );
        callwndproc_hook = NULL;
    }

    if (hook_thread_event) /* if thread is not started yet */
    {
        WaitForSingleObject(hook_thread_event, INFINITE);
        CloseHandle(hook_thread_event);
        hook_thread_event = NULL;
    }

    PostThreadMessageW( hook_thread_id, WM_USER+0x10, 1, 0 );

    LeaveCriticalSection(&dinput_hook_crit);
}