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
struct TYPE_3__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  message; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ MSG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  KeyDownData (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_RETURN ; 
 int /*<<< orphan*/  WM_KEYDOWN ; 

__attribute__((used)) static void FormEnterMsg (MSG *pMsg, HWND hwnd)
{
    pMsg->hwnd = hwnd;
    pMsg->message = WM_KEYDOWN;
    pMsg->wParam = VK_RETURN;
    pMsg->lParam = KeyDownData (1, 0x1C, 0, 0);
    /* pMsg->time is not set.  It shouldn't be needed */
    /* pMsg->pt is ignored */
}