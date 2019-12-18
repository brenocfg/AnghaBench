#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_separations ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
struct TYPE_4__ {int w; int h; int n; int alpha; int xres; int yres; int pagenum; int /*<<< orphan*/  (* header ) (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  seps; scalar_t__ line; int /*<<< orphan*/  s; int /*<<< orphan*/ * band; } ;
typedef  TYPE_1__ fz_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_count_active_separations (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_keep_separations (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

void fz_write_header(fz_context *ctx, fz_band_writer *writer, int w, int h, int n, int alpha, int xres, int yres, int pagenum, fz_colorspace *cs, fz_separations *seps)
{
	if (writer == NULL || writer->band == NULL)
		return;

	writer->w = w;
	writer->h = h;
	writer->s = fz_count_active_separations(ctx, seps);
	writer->n = n;
	writer->alpha = alpha;
	writer->xres = xres;
	writer->yres = yres;
	writer->pagenum = pagenum;
	writer->line = 0;
	writer->seps = fz_keep_separations(ctx, seps);
	writer->header(ctx, writer, cs);
}