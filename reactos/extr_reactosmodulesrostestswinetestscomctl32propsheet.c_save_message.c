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
struct message {int message; int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  PROPSHEET_SEQ_INDEX ; 
 int WM_ERASEBKGND ; 
 int WM_GETICON ; 
 int WM_GETTEXT ; 
 int WM_IME_NOTIFY ; 
 int WM_IME_SETCONTEXT ; 
 int WM_MOUSEFIRST ; 
 int WM_MOUSEHWHEEL ; 
 int WM_NCCREATE ; 
 int WM_NCMBUTTONDBLCLK ; 
 int WM_PAINT ; 
 int WM_SETCURSOR ; 
 int WM_USER ; 
 int /*<<< orphan*/  add_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct message*) ; 
 int id ; 
 int lparam ; 
 int sent ; 
 int /*<<< orphan*/  sequences ; 
 int wparam ; 

__attribute__((used)) static void save_message(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, INT receiver)
{
    struct message msg = { 0 };

    if (message < WM_USER &&
        message != WM_GETICON &&
        message != WM_GETTEXT &&
        message != WM_IME_SETCONTEXT &&
        message != WM_IME_NOTIFY &&
        message != WM_PAINT &&
        message != WM_ERASEBKGND &&
        message != WM_SETCURSOR &&
        (message < WM_NCCREATE || message > WM_NCMBUTTONDBLCLK) &&
        (message < WM_MOUSEFIRST || message > WM_MOUSEHWHEEL) &&
        message != 0x90)
    {
        msg.message = message;
        msg.flags = sent|wparam|lparam|id;
        msg.wParam = wParam;
        msg.lParam = lParam;
        msg.id = receiver;
        add_message(sequences, PROPSHEET_SEQ_INDEX, &msg);
    }
}