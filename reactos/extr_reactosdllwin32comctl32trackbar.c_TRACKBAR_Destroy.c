#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; struct TYPE_4__* tics; scalar_t__ hwndToolTip; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CloseThemeData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
TRACKBAR_Destroy (TRACKBAR_INFO *infoPtr)
{
    /* delete tooltip control */
    if (infoPtr->hwndToolTip)
    	DestroyWindow (infoPtr->hwndToolTip);

    Free (infoPtr->tics);
    infoPtr->tics = NULL;

    SetWindowLongPtrW (infoPtr->hwndSelf, 0, 0);
    CloseThemeData (GetWindowTheme (infoPtr->hwndSelf));
    Free (infoPtr);

    return 0;
}