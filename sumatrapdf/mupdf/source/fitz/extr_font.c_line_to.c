#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct closure {int /*<<< orphan*/  trm; int /*<<< orphan*/ * path; int /*<<< orphan*/ * ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_point ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ FT_Vector ;

/* Variables and functions */
 int /*<<< orphan*/  fz_lineto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fz_transform_point_xy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int line_to(const FT_Vector *p, void *cc_)
{
	struct closure *cc = (struct closure *)cc_;
	fz_context *ctx = cc->ctx;
	fz_path *path = cc->path;
	fz_point pt;

	pt = fz_transform_point_xy(p->x, p->y, cc->trm);
	fz_lineto(ctx, path, pt.x, pt.y);
	return 0;
}