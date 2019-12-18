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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_7__ {scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  wnd; } ;
struct TYPE_5__ {int /*<<< orphan*/  gc; int /*<<< orphan*/  backstore; } ;
struct TYPE_6__ {TYPE_1__ xwin; int /*<<< orphan*/  wnd; scalar_t__ ownbackstore; int /*<<< orphan*/  display; scalar_t__ Unobscured; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 TYPE_4__* sw ; 

void
ui_screenblt(RDPCLIENT * This, uint8 opcode,
	     /* dest */ int x, int y, int cx, int cy,
	     /* src */ int srcx, int srcy)
{
	SET_FUNCTION(opcode);
	if (This->ownbackstore)
	{
		XCopyArea(This->display, This->Unobscured ? This->wnd : This->xwin.backstore,
			  This->wnd, This->xwin.gc, srcx, srcy, cx, cy, x, y);
		XCopyArea(This->display, This->xwin.backstore, This->xwin.backstore, This->xwin.gc, srcx, srcy, cx, cy, x, y);
	}
	else
	{
		XCopyArea(This->display, This->wnd, This->wnd, This->xwin.gc, srcx, srcy, cx, cy, x, y);
	}

	ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
				(This->display, This->ownbackstore ? This->xwin.backstore : This->wnd,
				 sw->wnd, This->xwin.gc, x, y, cx, cy, x - sw->xoffset, y - sw->yoffset));

	RESET_FUNCTION(opcode);
}