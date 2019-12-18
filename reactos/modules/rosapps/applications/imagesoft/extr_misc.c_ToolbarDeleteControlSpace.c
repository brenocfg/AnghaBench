#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hWndControl; } ;
struct TYPE_5__ {int fsStyle; scalar_t__ dwData; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  TYPE_2__* PTBCUSTCTL ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int TBSTYLE_SEP ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
ToolbarDeleteControlSpace(HWND hWndToolbar,
                          const TBBUTTON *ptbButton)
{
    if ((ptbButton->fsStyle & TBSTYLE_SEP) &&
        ptbButton->dwData != 0)
    {
        PTBCUSTCTL cctl = (PTBCUSTCTL)ptbButton->dwData;

        DestroyWindow(cctl->hWndControl);

        HeapFree(ProcessHeap,
                 0,
                 cctl);
        return TRUE;
    }

    return FALSE;
}