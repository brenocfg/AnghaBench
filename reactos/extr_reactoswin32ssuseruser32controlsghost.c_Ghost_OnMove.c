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
struct TYPE_3__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Ghost_GetTarget (int /*<<< orphan*/ ) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOOWNERZORDER ; 
 int SWP_NOSENDCHANGING ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
Ghost_OnMove(HWND hwnd, int x, int y)
{
    RECT rc;
    HWND hwndTarget = Ghost_GetTarget(hwnd);

    GetWindowRect(hwnd, &rc);

    // move the target
    SetWindowPos(hwndTarget, NULL, rc.left, rc.top, 0, 0,
                 SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE |
                 SWP_NOSENDCHANGING);
}