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
typedef  int /*<<< orphan*/  fz_rect ;
struct TYPE_5__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 float atan2f (float,float) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float) ; 
 int /*<<< orphan*/  fz_expand_rect (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  fz_include_point_in_rect (int /*<<< orphan*/ ,TYPE_1__) ; 
 TYPE_1__ fz_make_point (float,float) ; 
 float fz_max (int,float) ; 
 TYPE_1__ rotate_vector (float,float,float) ; 

__attribute__((used)) static void pdf_write_arrow_appearance(fz_context *ctx, fz_buffer *buf, fz_rect *rect, float x, float y, float dx, float dy, float w)
{
	float r = fz_max(1, w);
	float angle = atan2f(dy, dx);
	fz_point v, a, b;

	v = rotate_vector(angle, 8.8f*r, 4.5f*r);
	a = fz_make_point(x + v.x, y + v.y);
	v = rotate_vector(angle, 8.8f*r, -4.5f*r);
	b = fz_make_point(x + v.x, y + v.y);

	*rect = fz_include_point_in_rect(*rect, a);
	*rect = fz_include_point_in_rect(*rect, b);
	*rect = fz_expand_rect(*rect, w);

	fz_append_printf(ctx, buf, "%g %g m\n", a.x, a.y);
	fz_append_printf(ctx, buf, "%g %g l\n", x, y);
	fz_append_printf(ctx, buf, "%g %g l\n", b.x, b.y);
}