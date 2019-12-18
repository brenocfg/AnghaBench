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
struct TYPE_3__ {int priority; } ;
typedef  TYPE_1__ vimmenu_T ;
typedef  int /*<<< orphan*/  PtWidget_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtGetResource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PtWidgetBrotherInFront (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PtWidgetChildBack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtWidgetInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PtWidgetParent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pt_ARG_POINTER ; 

__attribute__((used)) static void
gui_ph_position_menu(PtWidget_t *widget, int priority)
{
    PtWidget_t	*traverse;
    vimmenu_T	*menu;

    traverse = PtWidgetChildBack(PtWidgetParent(widget));

    /* Iterate through the list of widgets in traverse, until
     * we find the position we want to insert our widget into */
    /* TODO: traverse from front to back, possible speedup? */
    while (traverse != NULL)
    {
	PtGetResource(traverse, Pt_ARG_POINTER, &menu, 0);

	if (menu != NULL &&
		priority < menu->priority &&
		widget != traverse)
	{
	    /* Insert the widget before the current traverse widget */
	    PtWidgetInsert(widget, traverse, 1);
	    return;
	}

	traverse = PtWidgetBrotherInFront(traverse);
    }
}