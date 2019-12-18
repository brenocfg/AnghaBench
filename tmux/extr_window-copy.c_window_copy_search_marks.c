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
struct window_mode_entry {struct window_copy_mode_data* data; } ;
struct window_copy_mode_data {scalar_t__ cx; scalar_t__ cy; scalar_t__ oy; int searchthis; scalar_t__ searchcount; int /*<<< orphan*/  searchmark; int /*<<< orphan*/  searchstr; struct screen* backing; } ;
struct screen_write_ctx {int dummy; } ;
struct screen {struct grid* grid; } ;
struct grid {int hsize; int sy; int sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_alloc (int) ; 
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_default_cell ; 
 int /*<<< orphan*/  screen_free (struct screen*) ; 
 int /*<<< orphan*/  screen_init (struct screen*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_nputs (struct screen_write_ctx*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,int /*<<< orphan*/ *,struct screen*) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 
 scalar_t__ screen_write_strlen (char*,int /*<<< orphan*/ ) ; 
 int window_copy_is_lowercase (int /*<<< orphan*/ ) ; 
 int window_copy_search_lr (struct grid*,struct grid*,scalar_t__*,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static int
window_copy_search_marks(struct window_mode_entry *wme, struct screen *ssp)
{
	struct window_copy_mode_data	*data = wme->data;
	struct screen			*s = data->backing, ss;
	struct screen_write_ctx		 ctx;
	struct grid			*gd = s->grid;
	int				 found, cis, which = -1;
	u_int				 px, py, b, nfound = 0, width;

	if (ssp == NULL) {
		width = screen_write_strlen("%s", data->searchstr);
		screen_init(&ss, width, 1, 0);
		screen_write_start(&ctx, NULL, &ss);
		screen_write_nputs(&ctx, -1, &grid_default_cell, "%s",
		    data->searchstr);
		screen_write_stop(&ctx);
		ssp = &ss;
	} else
		width = screen_size_x(ssp);

	cis = window_copy_is_lowercase(data->searchstr);

	free(data->searchmark);
	data->searchmark = bit_alloc((gd->hsize + gd->sy) * gd->sx);

	for (py = 0; py < gd->hsize + gd->sy; py++) {
		px = 0;
		for (;;) {
			found = window_copy_search_lr(gd, ssp->grid, &px, py,
			    px, gd->sx, cis);
			if (!found)
				break;

			nfound++;
			if (px == data->cx && py == gd->hsize + data->cy - data->oy)
				which = nfound;

			b = (py * gd->sx) + px;
			bit_nset(data->searchmark, b, b + width - 1);

			px++;
		}
	}

	if (which != -1)
		data->searchthis = 1 + nfound - which;
	else
		data->searchthis = -1;
	data->searchcount = nfound;

	if (ssp == &ss)
		screen_free(&ss);
	return (nfound);
}