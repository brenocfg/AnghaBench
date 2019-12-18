#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float x; float y; } ;
struct TYPE_9__ {scalar_t__ cmd_len; TYPE_1__ current; scalar_t__ packed; } ;
typedef  TYPE_2__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_DEGENLINETO ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  FZ_HORIZTO ; 
 int /*<<< orphan*/  FZ_LINETO ; 
 scalar_t__ FZ_MOVETO ; 
 int /*<<< orphan*/  FZ_VERTTO ; 
 scalar_t__ LAST_CMD (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  push_cmd (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_coord (int /*<<< orphan*/ *,TYPE_2__*,float,float) ; 
 int /*<<< orphan*/  push_ord (int /*<<< orphan*/ *,TYPE_2__*,float,int) ; 

void
fz_lineto(fz_context *ctx, fz_path *path, float x, float y)
{
	float x0, y0;

	if (path->packed)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot modify a packed path");

	x0 = path->current.x;
	y0 = path->current.y;

	if (path->cmd_len == 0)
	{
		fz_warn(ctx, "lineto with no current point");
		return;
	}

	/* (Anything other than MoveTo) followed by (LineTo the same place) is a nop */
	if (LAST_CMD(path) != FZ_MOVETO && x0 == x && y0 == y)
		return;

	if (x0 == x)
	{
		if (y0 == y)
		{
			if (LAST_CMD(path) != FZ_MOVETO)
				return;
			push_cmd(ctx, path, FZ_DEGENLINETO);
		}
		else
		{
			push_cmd(ctx, path, FZ_VERTTO);
			push_ord(ctx, path, y, 0);
		}
	}
	else if (y0 == y)
	{
		push_cmd(ctx, path, FZ_HORIZTO);
		push_ord(ctx, path, x, 1);
	}
	else
	{
		push_cmd(ctx, path, FZ_LINETO);
		push_coord(ctx, path, x, y);
	}
}