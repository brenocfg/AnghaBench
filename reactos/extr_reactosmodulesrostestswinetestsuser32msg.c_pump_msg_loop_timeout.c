#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct recvd_message {scalar_t__ message; int flags; char* descr; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; scalar_t__ hwnd; } ;
struct TYPE_4__ {scalar_t__ message; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; scalar_t__ hwnd; } ;
typedef  TYPE_1__ MSG ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int GetTickCount () ; 
 int /*<<< orphan*/  MOUSEEVENTF_MOVE ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WM_SYSTIMER ; 
 scalar_t__ WM_TIMER ; 
 int /*<<< orphan*/  add_message (struct recvd_message*) ; 
 int lparam ; 
 int /*<<< orphan*/  mouse_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sent ; 
 int wparam ; 

__attribute__((used)) static void pump_msg_loop_timeout(DWORD timeout, BOOL inject_mouse_move)
{
    MSG msg;
    DWORD start_ticks, end_ticks;

    start_ticks = GetTickCount();
    /* add some deviation (50%) to cover not expected delays */
    start_ticks += timeout / 2;

    do
    {
        while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {
            /* Timer proc messages are not dispatched to the window proc,
             * and therefore not logged.
             */
            if ((msg.message == WM_TIMER || msg.message == WM_SYSTIMER) && msg.hwnd)
            {
                struct recvd_message s_msg;

                s_msg.hwnd = msg.hwnd;
                s_msg.message = msg.message;
                s_msg.flags = sent|wparam|lparam;
                s_msg.wParam = msg.wParam;
                s_msg.lParam = msg.lParam;
                s_msg.descr = "msg_loop";
                add_message(&s_msg);
            }
            DispatchMessageA(&msg);
        }

        end_ticks = GetTickCount();

        /* inject WM_MOUSEMOVE to see how it changes tracking */
        if (inject_mouse_move && start_ticks + timeout / 2 >= end_ticks)
        {
            mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0, 0);
            mouse_event(MOUSEEVENTF_MOVE, 1, 0, 0, 0);

            inject_mouse_move = FALSE;
        }
    } while (start_ticks + timeout >= end_ticks);
}