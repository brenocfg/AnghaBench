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
struct TYPE_6__ {TYPE_1__ xwin; int /*<<< orphan*/  display; scalar_t__ ownbackstore; int /*<<< orphan*/  wnd; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  ON_ALL_SEAMLESS_WINDOWS (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 TYPE_4__* sw ; 

void
ui_memblt(RDPCLIENT * This, uint8 opcode,
	  /* dest */ int x, int y, int cx, int cy,
	  /* src */ HBITMAP src, int srcx, int srcy)
{
	SET_FUNCTION(opcode);
	XCopyArea(This->display, (Pixmap) src, This->wnd, This->xwin.gc, srcx, srcy, cx, cy, x, y);
	ON_ALL_SEAMLESS_WINDOWS(XCopyArea,
				(This->display, (Pixmap) src, sw->wnd, This->xwin.gc,
				 srcx, srcy, cx, cy, x - sw->xoffset, y - sw->yoffset));
	if (This->ownbackstore)
		XCopyArea(This->display, (Pixmap) src, This->xwin.backstore, This->xwin.gc, srcx, srcy, cx, cy, x, y);
	RESET_FUNCTION(opcode);
}