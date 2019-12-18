#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  out; } ;
struct TYPE_4__ {TYPE_1__ super; int /*<<< orphan*/  pwg; } ;
typedef  TYPE_2__ pwg_band_writer ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  pwg_page_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pwg_write_mono_header(fz_context *ctx, fz_band_writer *writer_, fz_colorspace *cs)
{
	pwg_band_writer *writer = (pwg_band_writer *)writer_;

	pwg_page_header(ctx, writer->super.out, &writer->pwg,
		writer->super.xres, writer->super.yres, writer->super.w, writer->super.h, 1);
}