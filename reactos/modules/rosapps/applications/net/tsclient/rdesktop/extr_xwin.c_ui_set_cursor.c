#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  wnd; } ;
struct TYPE_5__ {scalar_t__ current_cursor; } ;
struct TYPE_6__ {TYPE_1__ xwin; int /*<<< orphan*/  display; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  scalar_t__ HCURSOR ;
typedef  scalar_t__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* sw ; 

void
ui_set_cursor(RDPCLIENT * This, HCURSOR cursor)
{
	This->xwin.current_cursor = (Cursor) cursor;
	XDefineCursor(This->display, This->wnd, This->xwin.current_cursor);
	ON_ALL_SEAMLESS_WINDOWS(XDefineCursor, (This->display, sw->wnd, This->xwin.current_cursor));
}