#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ packed; struct TYPE_5__* coords; struct TYPE_5__* cmds; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_PATH_PACKED_FLAT ; 
 scalar_t__ FZ_PATH_UNPACKED ; 
 scalar_t__ fz_drop_imp8 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_path(fz_context *ctx, const fz_path *pathc)
{
	fz_path *path = (fz_path *)pathc; /* Explicit cast away of const */

	if (fz_drop_imp8(ctx, path, &path->refs))
	{
		if (path->packed != FZ_PATH_PACKED_FLAT)
		{
			fz_free(ctx, path->cmds);
			fz_free(ctx, path->coords);
		}
		if (path->packed == FZ_PATH_UNPACKED)
			fz_free(ctx, path);
	}
}