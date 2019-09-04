#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct recvd_message {scalar_t__ message; int flags; char* descr; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  hwnd; } ;
struct TYPE_6__ {scalar_t__ message; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ MSG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HACCEL ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageA (TYPE_1__*) ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 scalar_t__ PeekMessageA (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TranslateAcceleratorA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_1__*) ; 
 scalar_t__ WM_MOUSEMOVE ; 
 scalar_t__ WM_TIMER ; 
 int /*<<< orphan*/  add_message (struct recvd_message*) ; 
 scalar_t__ ignore_message (scalar_t__) ; 
 int lparam ; 
 int wparam ; 

__attribute__((used)) static void pump_msg_loop(HWND hwnd, HACCEL hAccel)
{
    MSG msg;

    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
    {
        struct recvd_message log_msg;

        /* ignore some unwanted messages */
        if (msg.message == WM_MOUSEMOVE ||
            msg.message == WM_TIMER ||
            ignore_message( msg.message ))
            continue;

        log_msg.hwnd = msg.hwnd;
        log_msg.message = msg.message;
        log_msg.flags = wparam|lparam;
        log_msg.wParam = msg.wParam;
        log_msg.lParam = msg.lParam;
        log_msg.descr = "accel";
        add_message(&log_msg);

        if (!hAccel || !TranslateAcceleratorA(hwnd, hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
}