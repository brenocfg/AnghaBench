#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bbox; int /*<<< orphan*/  matrix; } ;
typedef  TYPE_1__ fz_shade ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_LINEAR ; 
 scalar_t__ FZ_RADIAL ; 
 int /*<<< orphan*/  fz_bound_mesh (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_intersect_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_transform_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fz_rect
fz_bound_shade(fz_context *ctx, fz_shade *shade, fz_matrix ctm)
{
	ctm = fz_concat(shade->matrix, ctm);
	if (shade->type != FZ_LINEAR && shade->type != FZ_RADIAL)
	{
		fz_rect rect = fz_bound_mesh(ctx, shade);
		rect = fz_intersect_rect(rect, shade->bbox);
		return fz_transform_rect(rect, ctm);
	}
	return fz_transform_rect(shade->bbox, ctm);
}