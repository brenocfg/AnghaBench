#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct paint_tri_data {int /*<<< orphan*/  bbox; TYPE_1__* dest; } ;
typedef  int /*<<< orphan*/  fz_vertex ;
struct TYPE_3__ {scalar_t__ alpha; scalar_t__ n; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_paint_triangle (TYPE_1__*,float**,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_paint_tri(fz_context *ctx, void *arg, fz_vertex *av, fz_vertex *bv, fz_vertex *cv)
{
	struct paint_tri_data *ptd = (struct paint_tri_data *)arg;
	float *vertices[3];
	fz_pixmap *dest;

	vertices[0] = (float *)av;
	vertices[1] = (float *)bv;
	vertices[2] = (float *)cv;

	dest = ptd->dest;
	fz_paint_triangle(dest, vertices, 2 + dest->n - dest->alpha, ptd->bbox);
}