#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int features; } ;
struct TYPE_4__ {int /*<<< orphan*/ * out; } ;
struct TYPE_6__ {TYPE_2__ options; TYPE_1__ super; } ;
typedef  TYPE_3__ mono_pcl_band_writer ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int HACK__IS_A_OCE9050 ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
mono_pcl_write_trailer(fz_context *ctx, fz_band_writer *writer_)
{
	mono_pcl_band_writer *writer = (mono_pcl_band_writer *)writer_;
	fz_output *out = writer->super.out;

	/* end raster graphics and eject page */
	fz_write_string(ctx, out, "\033*rB\f");

	if (writer->options.features & HACK__IS_A_OCE9050)
	{
		/* Pen up, pen select, advance full page, reset */
		fz_write_string(ctx, out, "\033%1BPUSP0PG;\033E");
	}
}