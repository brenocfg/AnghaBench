#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct TYPE_8__ {TYPE_1__ m; } ;
struct TYPE_9__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_shade ;
struct TYPE_10__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
typedef  TYPE_4__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static fz_rect
fz_bound_mesh_type4567(fz_context *ctx, fz_shade *shade)
{
	fz_rect bbox;
	bbox.x0 = shade->u.m.x0;
	bbox.y0 = shade->u.m.y0;
	bbox.x1 = shade->u.m.x1;
	bbox.y1 = shade->u.m.y1;
	return bbox;
}