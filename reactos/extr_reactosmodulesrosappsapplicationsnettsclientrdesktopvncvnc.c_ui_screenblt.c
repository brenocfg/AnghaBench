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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  vncCopyBlit (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 scalar_t__ vncwinClipRect (int*,int*,int*,int*) ; 

void
ui_screenblt(uint8 opcode,
	     /* dest */ int x, int y, int cx, int cy,
	     /* src */ int srcx, int srcy)
{
	int ox, oy;

	ox = x;
	oy = y;
	if (vncwinClipRect(&x, &y, &cx, &cy))
	{
		//if we clipped top or left, we have to adjust srcx,srcy;
		srcx += x - ox;
		srcy += y - oy;
		vncCopyBlit(server, x, y, cx, cy, srcx, srcy);
	}
}