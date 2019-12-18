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
typedef  int /*<<< orphan*/  fz_pwg_options ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bitmap ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_bitmap_as_pwg_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fz_write_pwg_file_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
fz_write_bitmap_as_pwg(fz_context *ctx, fz_output *out, const fz_bitmap *bitmap, const fz_pwg_options *pwg)
{
	fz_write_pwg_file_header(ctx, out);
	fz_write_bitmap_as_pwg_page(ctx, out, bitmap, pwg);
}