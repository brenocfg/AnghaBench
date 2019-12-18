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
struct window_mode_entry {int dummy; } ;
struct screen_write_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  window_copy_write_line (struct window_mode_entry*,struct screen_write_ctx*,scalar_t__) ; 

__attribute__((used)) static void
window_copy_write_lines(struct window_mode_entry *wme,
    struct screen_write_ctx *ctx, u_int py, u_int ny)
{
	u_int	yy;

	for (yy = py; yy < py + ny; yy++)
		window_copy_write_line(wme, ctx, py);
}