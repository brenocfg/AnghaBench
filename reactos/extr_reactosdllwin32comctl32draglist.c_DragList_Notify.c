#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  ptCursor; int /*<<< orphan*/  uNotification; int /*<<< orphan*/  hWnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ DRAGLISTINFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetCursorPos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgCtrlID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uDragListMessage ; 

__attribute__((used)) static LRESULT DragList_Notify(HWND hwndLB, UINT uNotification)
{
    DRAGLISTINFO dli;
    dli.hWnd = hwndLB;
    dli.uNotification = uNotification;
    GetCursorPos(&dli.ptCursor);
    return SendMessageW(GetParent(hwndLB), uDragListMessage, GetDlgCtrlID(hwndLB), (LPARAM)&dli);
}