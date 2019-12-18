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
struct info {unsigned char image_left; unsigned char image_top; unsigned char image_width; unsigned char image_height; unsigned char has_lct; unsigned char image_interlaced; int lct_entries; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const unsigned char *
gif_read_id(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	if (end - p < 10)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in image descriptor in gif image");

	info->image_left = p[2] << 8 | p[1];
	info->image_top = p[4] << 8 | p[3];
	info->image_width = p[6] << 8 | p[5];
	info->image_height = p[8] << 8 | p[7];
	info->has_lct = (p[9] >> 7) & 0x1;
	info->image_interlaced = (p[9] >> 6) & 0x1;

	if (info->has_lct)
		info->lct_entries = 1 << ((p[9] & 0x7) + 1);

	return p + 10;
}