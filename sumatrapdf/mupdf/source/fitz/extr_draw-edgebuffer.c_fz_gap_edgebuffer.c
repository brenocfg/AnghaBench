#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_output ;
struct TYPE_6__ {TYPE_1__* cursor; scalar_t__ app; } ;
typedef  TYPE_2__ fz_edgebuffer ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int unset; int can_save; void* d; scalar_t__ saved; } ;

/* Variables and functions */
 void* DIRN_UNSET ; 
 int /*<<< orphan*/  cursor_flush (TYPE_2__*) ; 
 scalar_t__ debugging_scan_converter ; 
 int /*<<< orphan*/  fz_edgebuffer_print_app (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * fz_stderr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void fz_gap_edgebuffer(fz_context *ctx, fz_rasterizer *ras)
{
	fz_edgebuffer *eb = (fz_edgebuffer *)ras;

	if (eb->app)
	{
#ifdef DEBUG_SCAN_CONVERTER
		if (0 && debugging_scan_converter)
		{
			fz_output *err = fz_stderr(ctx);
			fz_write_printf(ctx, fz_stderr(ctx), "Pen up move.\n");
			fz_write_printf(ctx, err, "Before flush:\n");
			fz_edgebuffer_print_app(ctx, err, eb);
		}
#endif
		cursor_flush(eb);
		eb->cursor[0].saved = 0;
		eb->cursor[0].unset = 1;
		eb->cursor[0].can_save = 1;
		eb->cursor[0].d = DIRN_UNSET;
		eb->cursor[1].saved = 0;
		eb->cursor[1].unset = 1;
		eb->cursor[1].can_save = 1;
		eb->cursor[1].d = DIRN_UNSET;
		eb->cursor[2].saved = 0;
		eb->cursor[2].unset = 1;
		eb->cursor[2].can_save = 1;
		eb->cursor[2].d = DIRN_UNSET;
	}
}