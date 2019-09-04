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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PostThreadMessageW (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WM_USER ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dinput_hook_crit ; 
 int /*<<< orphan*/  direct_input_list ; 
 int /*<<< orphan*/ * hook_thread_event ; 
 scalar_t__ hook_thread_id ; 
 int /*<<< orphan*/  hook_thread_proc ; 
 int /*<<< orphan*/  list_count (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_hook_thread(void)
{
    static HANDLE hook_thread;

    EnterCriticalSection(&dinput_hook_crit);

    TRACE("IDirectInputs left: %d\n", list_count(&direct_input_list));
    if (!list_empty(&direct_input_list) && !hook_thread)
    {
        hook_thread_event = CreateEventW(NULL, FALSE, FALSE, NULL);
        hook_thread = CreateThread(NULL, 0, hook_thread_proc, hook_thread_event, 0, &hook_thread_id);
        LeaveCriticalSection(&dinput_hook_crit);
    }
    else if (list_empty(&direct_input_list) && hook_thread)
    {
        DWORD tid = hook_thread_id;

        if (hook_thread_event) /* if thread is not started yet */
        {
            WaitForSingleObject(hook_thread_event, INFINITE);
            CloseHandle(hook_thread_event);
            hook_thread_event = NULL;
        }

        hook_thread_id = 0;
        PostThreadMessageW(tid, WM_USER+0x10, 0, 0);
        LeaveCriticalSection(&dinput_hook_crit);

        /* wait for hook thread to exit */
        WaitForSingleObject(hook_thread, INFINITE);
        CloseHandle(hook_thread);
        hook_thread = NULL;
    }
    else
        LeaveCriticalSection(&dinput_hook_crit);

    return hook_thread_id != 0;
}