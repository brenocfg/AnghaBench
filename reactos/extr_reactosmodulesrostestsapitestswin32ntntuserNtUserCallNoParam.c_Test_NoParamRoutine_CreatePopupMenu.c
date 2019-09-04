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
typedef  scalar_t__ HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyMenu (scalar_t__) ; 
 scalar_t__ IsMenu (scalar_t__) ; 
 scalar_t__ NtUserCallNoParam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _NOPARAM_ROUTINE_CREATEMENUPOPUP ; 

void
Test_NoParamRoutine_CreatePopupMenu(void) /* 1 */
{
    HMENU hMenu;

    hMenu = (HMENU)NtUserCallNoParam(_NOPARAM_ROUTINE_CREATEMENUPOPUP);
    TEST(IsMenu(hMenu) == TRUE);
    DestroyMenu(hMenu);

}