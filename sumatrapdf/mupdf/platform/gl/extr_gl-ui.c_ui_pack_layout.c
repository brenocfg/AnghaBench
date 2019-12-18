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
struct TYPE_6__ {int x0; int x1; int y0; int y1; } ;
typedef  TYPE_2__ fz_irect ;
typedef  enum side { ____Placeholder_side } side ;
typedef  enum fill { ____Placeholder_fill } fill ;
typedef  enum anchor { ____Placeholder_anchor } anchor ;
struct TYPE_7__ {TYPE_1__* cavity; } ;
struct TYPE_5__ {int x0; int x1; int y0; int y1; } ;

/* Variables and functions */
#define  ALL 141 
#define  B 140 
#define  CENTER 139 
#define  E 138 
#define  L 137 
#define  N 136 
#define  NE 135 
#define  NW 134 
#define  R 133 
#define  S 132 
#define  SE 131 
#define  SW 130 
#define  T 129 
#define  W 128 
 int X ; 
 int Y ; 
 TYPE_4__ ui ; 

fz_irect ui_pack_layout(int slave_w, int slave_h, enum side side, enum fill fill, enum anchor anchor, int padx, int pady)
{
	fz_irect parcel, slave;
	int parcel_w, parcel_h;
	int anchor_x, anchor_y;

	switch (side)
	{
	default:
	case ALL:
		parcel.x0 = ui.cavity->x0 + padx;
		parcel.x1 = ui.cavity->x1 - padx;
		parcel.y0 = ui.cavity->y0 + pady;
		parcel.y1 = ui.cavity->y1 - pady;
		ui.cavity->x0 = ui.cavity->x1;
		ui.cavity->y0 = ui.cavity->y1;
		break;
	case T:
		parcel.x0 = ui.cavity->x0 + padx;
		parcel.x1 = ui.cavity->x1 - padx;
		parcel.y0 = ui.cavity->y0 + pady;
		parcel.y1 = ui.cavity->y0 + pady + slave_h;
		ui.cavity->y0 = parcel.y1 + pady;
		break;
	case B:
		parcel.x0 = ui.cavity->x0 + padx;
		parcel.x1 = ui.cavity->x1 - padx;
		parcel.y0 = ui.cavity->y1 - pady - slave_h;
		parcel.y1 = ui.cavity->y1 - pady;
		ui.cavity->y1 = parcel.y0 - pady;
		break;
	case L:
		parcel.x0 = ui.cavity->x0 + padx;
		parcel.x1 = ui.cavity->x0 + padx + slave_w;
		parcel.y0 = ui.cavity->y0 + pady;
		parcel.y1 = ui.cavity->y1 - pady;
		ui.cavity->x0 = parcel.x1 + padx;
		break;
	case R:
		parcel.x0 = ui.cavity->x1 - padx - slave_w;
		parcel.x1 = ui.cavity->x1 - padx;
		parcel.y0 = ui.cavity->y0 + pady;
		parcel.y1 = ui.cavity->y1 - pady;
		ui.cavity->x1 = parcel.x0 - padx;
		break;
	}

	parcel_w = parcel.x1 - parcel.x0;
	parcel_h = parcel.y1 - parcel.y0;

	if (fill & X)
		slave_w = parcel_w;
	if (fill & Y)
		slave_h = parcel_h;

	anchor_x = parcel_w - slave_w;
	anchor_y = parcel_h - slave_h;

	switch (anchor)
	{
	default:
	case CENTER:
		slave.x0 = parcel.x0 + anchor_x / 2;
		slave.y0 = parcel.y0 + anchor_y / 2;
		break;
	case N:
		slave.x0 = parcel.x0 + anchor_x / 2;
		slave.y0 = parcel.y0;
		break;
	case NE:
		slave.x0 = parcel.x0 + anchor_x;
		slave.y0 = parcel.y0;
		break;
	case E:
		slave.x0 = parcel.x0 + anchor_x;
		slave.y0 = parcel.y0 + anchor_y / 2;
		break;
	case SE:
		slave.x0 = parcel.x0 + anchor_x;
		slave.y0 = parcel.y0 + anchor_y;
		break;
	case S:
		slave.x0 = parcel.x0 + anchor_x / 2;
		slave.y0 = parcel.y0 + anchor_y;
		break;
	case SW:
		slave.x0 = parcel.x0;
		slave.y0 = parcel.y0 + anchor_y;
		break;
	case W:
		slave.x0 = parcel.x0;
		slave.y0 = parcel.y0 + anchor_y / 2;
		break;
	case NW:
		slave.x0 = parcel.x0;
		slave.y0 = parcel.y0;
		break;
	}

	slave.x1 = slave.x0 + slave_w;
	slave.y1 = slave.y0 + slave_h;

	return slave;
}