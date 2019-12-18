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
typedef  int /*<<< orphan*/ * Widget ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 scalar_t__ False ; 
 int /*<<< orphan*/  XtDisplay (int /*<<< orphan*/ *) ; 
 scalar_t__ XtIsRealized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XtWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ isWindowMapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Boolean
isMapped(Widget widget)
{
	if (widget == NULL) {
		return(False);
	}

	if (XtIsRealized(widget) == False) {
		return(False);
	}

	return(isWindowMapped(XtDisplay(widget), XtWindow(widget)));
}