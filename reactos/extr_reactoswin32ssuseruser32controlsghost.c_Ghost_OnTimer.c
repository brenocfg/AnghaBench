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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int /*<<< orphan*/  hwndTarget; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ GHOST_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GHOST_INTERVAL ; 
 scalar_t__ GHOST_TIMER_ID ; 
 TYPE_1__* Ghost_GetData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ghost_Unenchant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsHungAppWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Ghost_OnTimer(HWND hwnd, UINT id)
{
    HWND hwndTarget;
    GHOST_DATA *pData = Ghost_GetData(hwnd);

    if (id != GHOST_TIMER_ID || !pData)
        return;

    // stop the timer
    KillTimer(hwnd, id);

    hwndTarget = pData->hwndTarget;
    if (!IsWindow(hwndTarget) || !IsHungAppWindow(hwndTarget))
    {
        // resume if window is destroyed or responding
        Ghost_Unenchant(hwnd, FALSE);
        return;
    }

    // restart the timer
    SetTimer(hwnd, GHOST_TIMER_ID, GHOST_INTERVAL, NULL);
}