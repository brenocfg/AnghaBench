#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 float CIRCLE_MAGIC ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float,...) ; 

__attribute__((used)) static void
draw_circle(fz_context *ctx, fz_buffer *buf, float rx, float ry, float cx, float cy)
{
	float mx = rx * CIRCLE_MAGIC;
	float my = ry * CIRCLE_MAGIC;
	fz_append_printf(ctx, buf, "%g %g m\n", cx, cy+ry);
	fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", cx+mx, cy+ry, cx+rx, cy+my, cx+rx, cy);
	fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", cx+rx, cy-my, cx+mx, cy-ry, cx, cy-ry);
	fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", cx-mx, cy-ry, cx-rx, cy-my, cx-rx, cy);
	fz_append_printf(ctx, buf, "%g %g %g %g %g %g c\n", cx-rx, cy+my, cx-mx, cy+ry, cx, cy+ry);
}