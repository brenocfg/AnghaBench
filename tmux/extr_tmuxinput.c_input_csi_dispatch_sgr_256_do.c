#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grid_cell {int fg; int bg; } ;
struct TYPE_2__ {struct grid_cell cell; } ;
struct input_ctx {TYPE_1__ cell; } ;

/* Variables and functions */
 int COLOUR_FLAG_256 ; 

__attribute__((used)) static int
input_csi_dispatch_sgr_256_do(struct input_ctx *ictx, int fgbg, int c)
{
	struct grid_cell	*gc = &ictx->cell.cell;

	if (c == -1 || c > 255) {
		if (fgbg == 38)
			gc->fg = 8;
		else if (fgbg == 48)
			gc->bg = 8;
	} else {
		if (fgbg == 38)
			gc->fg = c | COLOUR_FLAG_256;
		else if (fgbg == 48)
			gc->bg = c | COLOUR_FLAG_256;
	}
	return (1);
}