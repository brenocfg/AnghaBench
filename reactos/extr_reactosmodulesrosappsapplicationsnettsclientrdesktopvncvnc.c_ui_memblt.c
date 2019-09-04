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
typedef  int /*<<< orphan*/  vncBuffer ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
#define  ROP2_AND 131 
#define  ROP2_COPY 130 
#define  ROP2_OR 129 
 int ROP2_S (int /*<<< orphan*/ ) ; 
#define  ROP2_XOR 128 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  unimpl (char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  vncAndBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vncCopyBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vncTransBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vncXorBlitFrom (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ vncwinClipRect (int*,int*,int*,int*) ; 

void
ui_memblt(uint8 opcode,
	  /* dest */ int x, int y, int cx, int cy,
	  /* src */ HBITMAP src, int srcx, int srcy)
{
	int ox, oy;
	ox = x;
	oy = y;

	if (vncwinClipRect(&x, &y, &cx, &cy))
	{
		//if we clipped top or left, we have to adjust srcx,srcy;
		srcx += x - ox;
		srcy += y - oy;
		switch (ROP2_S(opcode))
		{
			case ROP2_OR:
				vncTransBlitFrom(server, x, y, cx, cy, (vncBuffer *) src, srcx,
						 srcy, 0x0);
				break;
			case ROP2_XOR:
				vncXorBlitFrom(server, x, y, cx, cy, (vncBuffer *) src, srcx, srcy);
				break;
			case ROP2_AND:
				vncAndBlitFrom(server, x, y, cx, cy, (vncBuffer *) src, srcx, srcy);
				break;
			case ROP2_COPY:
				vncCopyBlitFrom(server, x, y, cx, cy, (vncBuffer *) src, srcx,
						srcy);
				break;
			default:
				unimpl("ui_memblt: op%d %d,%d %dx%d\n", opcode, x, y, cx, cy);
				vncCopyBlitFrom(server, x, y, cx, cy, (vncBuffer *) src, srcx,
						srcy);
				break;
		}
	}
}