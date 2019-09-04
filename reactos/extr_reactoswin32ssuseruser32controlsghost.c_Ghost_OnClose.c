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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GHOST_INTERVAL ; 
 int /*<<< orphan*/  GHOST_TIMER_ID ; 
 int /*<<< orphan*/  Ghost_Unenchant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_ASK_TERMINATE ; 
 int /*<<< orphan*/  IDS_HUNG_UP_TITLE ; 
 scalar_t__ IDYES ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MB_ICONINFORMATION ; 
 int MB_YESNO ; 
 scalar_t__ MessageBoxW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  User32Instance ; 

__attribute__((used)) static void
Ghost_OnClose(HWND hwnd)
{
    INT id;
    WCHAR szAskTerminate[128];
    WCHAR szHungUpTitle[128];

    // stop timer
    KillTimer(hwnd, GHOST_TIMER_ID);

    LoadStringW(User32Instance, IDS_ASK_TERMINATE,
                szAskTerminate, ARRAYSIZE(szAskTerminate));
    LoadStringW(User32Instance, IDS_HUNG_UP_TITLE,
                szHungUpTitle, ARRAYSIZE(szHungUpTitle));

    id = MessageBoxW(hwnd, szAskTerminate, szHungUpTitle,
                     MB_ICONINFORMATION | MB_YESNO);
    if (id == IDYES)
    {
        // destroy the target
        Ghost_Unenchant(hwnd, TRUE);
        return;
    }

    // restart timer
    SetTimer(hwnd, GHOST_TIMER_ID, GHOST_INTERVAL, NULL);
}