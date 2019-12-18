#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float x; float y; } ;
struct TYPE_8__ {scalar_t__ cmd_len; float* coords; int coord_len; TYPE_1__ current; TYPE_1__ begin; scalar_t__ packed; } ;
typedef  TYPE_2__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ FZ_MOVETO ; 
 scalar_t__ LAST_CMD (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  push_cmd (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  push_coord (int /*<<< orphan*/ *,TYPE_2__*,float,float) ; 

void
fz_moveto(fz_context *ctx, fz_path *path, float x, float y)
{
	if (path->packed)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot modify a packed path");

	if (path->cmd_len > 0 && LAST_CMD(path) == FZ_MOVETO)
	{
		/* Collapse moveto followed by moveto. */
		path->coords[path->coord_len-2] = x;
		path->coords[path->coord_len-1] = y;
		path->current.x = x;
		path->current.y = y;
		path->begin = path->current;
		return;
	}

	push_cmd(ctx, path, FZ_MOVETO);
	push_coord(ctx, path, x, y);

	path->begin = path->current;
}