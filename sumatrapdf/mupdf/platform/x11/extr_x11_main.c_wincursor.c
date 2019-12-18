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
typedef  int /*<<< orphan*/  pdfapp_t ;

/* Variables and functions */
 int ARROW ; 
 int CARET ; 
 int HAND ; 
 int WAIT ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcarrow ; 
 int /*<<< orphan*/  xccaret ; 
 int /*<<< orphan*/  xchand ; 
 int /*<<< orphan*/  xcwait ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xwin ; 

void wincursor(pdfapp_t *app, int curs)
{
	if (curs == ARROW)
		XDefineCursor(xdpy, xwin, xcarrow);
	if (curs == HAND)
		XDefineCursor(xdpy, xwin, xchand);
	if (curs == WAIT)
		XDefineCursor(xdpy, xwin, xcwait);
	if (curs == CARET)
		XDefineCursor(xdpy, xwin, xccaret);
	XFlush(xdpy);
}