#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * color; int /*<<< orphan*/ ** pole; } ;
typedef  TYPE_1__ tensor_patch ;
struct TYPE_10__ {int /*<<< orphan*/  p; } ;
typedef  TYPE_2__ fz_vertex ;
typedef  int /*<<< orphan*/  fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_prepare_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paint_quad (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void
triangulate_patch(fz_context *ctx, fz_mesh_processor *painter, tensor_patch *p)
{
	fz_vertex v0, v1, v2, v3;

	v0.p = p->pole[0][0];
	v1.p = p->pole[0][3];
	v2.p = p->pole[3][3];
	v3.p = p->pole[3][0];

	fz_prepare_color(ctx, painter, &v0, p->color[0]);
	fz_prepare_color(ctx, painter, &v1, p->color[1]);
	fz_prepare_color(ctx, painter, &v2, p->color[2]);
	fz_prepare_color(ctx, painter, &v3, p->color[3]);

	paint_quad(ctx, painter, &v0, &v1, &v2, &v3);
}