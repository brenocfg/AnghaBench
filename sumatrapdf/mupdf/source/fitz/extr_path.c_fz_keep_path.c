#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int refs; scalar_t__ packed; } ;
typedef  TYPE_1__ fz_path ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_PATH_UNPACKED ; 
 TYPE_1__* fz_keep_imp8 (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  fz_trim_path (int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_path *
fz_keep_path(fz_context *ctx, const fz_path *pathc)
{
	fz_path *path = (fz_path *)pathc; /* Explicit cast away of const */

	if (path == NULL)
		return NULL;
	if (path->refs == 1 && path->packed == FZ_PATH_UNPACKED)
		fz_trim_path(ctx, path);
	return fz_keep_imp8(ctx, path, &path->refs);
}