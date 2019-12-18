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
struct TYPE_2__ {int fsStyle; } ;
typedef  TYPE_1__ TBBUTTON ;
typedef  scalar_t__ LPTBBUTTON ;
typedef  long LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int TBSTYLE_SEP ; 
 int /*<<< orphan*/  TB_BUTTONCOUNT ; 
 int /*<<< orphan*/  TB_GETBUTTON ; 
 int /*<<< orphan*/  TRUE ; 

BOOL LastButtonIsSeparator(HWND hwndTB)
{
    TBBUTTON button;

    INT count = (INT)SendMessage(hwndTB, TB_BUTTONCOUNT, 0, 0L);
    SendMessage(hwndTB, TB_GETBUTTON, count - 1, (LPARAM)(LPTBBUTTON)&button);

    return (button.fsStyle & TBSTYLE_SEP) ? TRUE : FALSE;
}