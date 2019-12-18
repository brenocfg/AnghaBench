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
struct screen {int dummy; } ;
struct format_ranges {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  format_update_ranges (struct format_ranges*,struct screen*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  screen_write_cursormove (struct screen_write_ctx*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_fast_copy (struct screen_write_ctx*,struct screen*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
format_draw_put(struct screen_write_ctx *octx, u_int ocx, u_int ocy,
    struct screen *s, struct format_ranges *frs, u_int offset, u_int start,
    u_int width)
{
	/*
	 * The offset is how far from the cursor on the target screen; start
	 * and width how much to copy from the source screen.
	 */
	screen_write_cursormove(octx, ocx + offset, ocy, 0);
	screen_write_fast_copy(octx, s, start, 0, width, 1);
	format_update_ranges(frs, s, offset, start, width);
}