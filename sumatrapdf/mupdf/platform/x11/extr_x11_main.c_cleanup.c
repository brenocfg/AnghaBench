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
struct TYPE_4__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ pdfapp_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdfapp_close (TYPE_1__*) ; 
 int /*<<< orphan*/  xcarrow ; 
 int /*<<< orphan*/  xccaret ; 
 int /*<<< orphan*/  xchand ; 
 int /*<<< orphan*/  xcwait ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xgc ; 
 int /*<<< orphan*/  xicon ; 
 int /*<<< orphan*/  xwin ; 

__attribute__((used)) static void cleanup(pdfapp_t *app)
{
	fz_context *ctx = app->ctx;

	pdfapp_close(app);

	XDestroyWindow(xdpy, xwin);

	XFreePixmap(xdpy, xicon);

	XFreeCursor(xdpy, xccaret);
	XFreeCursor(xdpy, xcwait);
	XFreeCursor(xdpy, xchand);
	XFreeCursor(xdpy, xcarrow);

	XFreeGC(xdpy, xgc);

	XCloseDisplay(xdpy);

	fz_drop_context(ctx);
}