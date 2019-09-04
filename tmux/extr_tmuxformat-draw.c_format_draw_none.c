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
typedef  scalar_t__ u_int ;
struct screen_write_ctx {int dummy; } ;
struct screen {scalar_t__ cx; } ;
struct format_ranges {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_draw_put (struct screen_write_ctx*,scalar_t__,scalar_t__,struct screen*,struct format_ranges*,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static void
format_draw_none(struct screen_write_ctx *octx, u_int available, u_int ocx,
    u_int ocy, struct screen *left, struct screen *centre, struct screen *right,
    struct format_ranges *frs)
{
	u_int	width_left, width_centre, width_right;

	width_left = left->cx;
	width_centre = centre->cx;
	width_right = right->cx;

	/*
	 * Try to keep as much of the left and right as possible at the expense
	 * of the centre.
	 */
	while (width_left + width_centre + width_right > available) {
		if (width_centre > 0)
			width_centre--;
		else if (width_right > 0)
			width_right--;
		else
			width_left--;
	}

	/* Write left. */
	format_draw_put(octx, ocx, ocy, left, frs, 0, 0, width_left);

	/* Write right at available - width_right. */
	format_draw_put(octx, ocx, ocy, right, frs,
	    available - width_right,
	    right->cx - width_right,
	    width_right);

	/*
	 * Write centre halfway between
	 *     width_left
	 * and
	 *     available - width_right.
	 */
	format_draw_put(octx, ocx, ocy, centre, frs,
	    width_left
	    + ((available - width_right) - width_left) / 2
	    - width_centre / 2,
	    centre->cx / 2 - width_centre / 2,
	    width_centre);
}