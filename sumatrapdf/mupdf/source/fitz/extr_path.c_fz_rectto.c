#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cmd_len; int coord_len; int /*<<< orphan*/  begin; int /*<<< orphan*/  current; scalar_t__ packed; } ;
typedef  TYPE_1__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ FZ_MOVETO ; 
 int /*<<< orphan*/  FZ_RECTTO ; 
 scalar_t__ LAST_CMD (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  push_cmd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_coord (int /*<<< orphan*/ *,TYPE_1__*,float,float) ; 

void
fz_rectto(fz_context *ctx, fz_path *path, float x1, float y1, float x2, float y2)
{
	if (path->packed)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot modify a packed path");

	if (path->cmd_len > 0 && LAST_CMD(path) == FZ_MOVETO)
	{
		/* Collapse moveto followed by rectto. */
		path->coord_len -= 2;
		path->cmd_len--;
	}

	push_cmd(ctx, path, FZ_RECTTO);
	push_coord(ctx, path, x1, y1);
	push_coord(ctx, path, x2, y2);

	path->current = path->begin;
}