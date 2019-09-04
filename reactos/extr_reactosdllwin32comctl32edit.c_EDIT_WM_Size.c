#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_SetRectNP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_UpdateText (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SIZE_MAXIMIZED ; 
 scalar_t__ SIZE_RESTORED ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void EDIT_WM_Size(EDITSTATE *es, UINT action)
{
	if ((action == SIZE_MAXIMIZED) || (action == SIZE_RESTORED)) {
		RECT rc;
		GetClientRect(es->hwndSelf, &rc);
		EDIT_SetRectNP(es, &rc);
		EDIT_UpdateText(es, NULL, TRUE);
	}
}