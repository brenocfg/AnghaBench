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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  ROP2_AND ; 
 int /*<<< orphan*/  ROP2_COPY ; 
 int /*<<< orphan*/  ROP2_NXOR ; 
 int /*<<< orphan*/  ROP2_XOR ; 
 int /*<<< orphan*/  ui_memblt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ui_patblt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
ui_triblt(uint8 opcode,
	  /* dest */ int x, int y, int cx, int cy,
	  /* src */ HBITMAP src, int srcx, int srcy,
	  /* brush */ BRUSH * brush, int bgcolour, int fgcolour)
{
	/* This is potentially difficult to do in general. Until someone
	   comes up with a more efficient way of doing it I am using cases. */

	switch (opcode)
	{
		case 0x69:	/* PDSxxn */
			ui_memblt(ROP2_XOR, x, y, cx, cy, src, srcx, srcy);
			ui_patblt(ROP2_NXOR, x, y, cx, cy, brush, bgcolour, fgcolour);
			break;

		case 0xb8:	/* PSDPxax */
			ui_patblt(ROP2_XOR, x, y, cx, cy, brush, bgcolour, fgcolour);
			ui_memblt(ROP2_AND, x, y, cx, cy, src, srcx, srcy);
			ui_patblt(ROP2_XOR, x, y, cx, cy, brush, bgcolour, fgcolour);
			break;

		default:
			unimpl("ui_triblt 1x%x\n", opcode);
			ui_memblt(ROP2_COPY, x, y, cx, cy, src, srcx, srcy);
	}

}