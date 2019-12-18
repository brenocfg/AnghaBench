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
typedef  scalar_t__ WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  long DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LB_SETANCHORINDEX ; 
 int /*<<< orphan*/  LB_SETCARETINDEX ; 
 int /*<<< orphan*/  LB_SETSEL ; 
 long MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  TRUE ; 

VOID
SelectItem(HWND hwndLB, WPARAM wParam, BOOL bSel)
{
   //
   // Add the current item to the selection.
   //
   SendMessage(hwndLB, LB_SETSEL, bSel, (DWORD)wParam);

   //
   // Give the selected item the focus rect and anchor pt.
   //
   SendMessage(hwndLB, LB_SETCARETINDEX, wParam, MAKELONG(TRUE,0));
   SendMessage(hwndLB, LB_SETANCHORINDEX, wParam, 0L);
}