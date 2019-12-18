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
struct info {unsigned char width; unsigned char height; unsigned char has_gct; int gct_entries; unsigned char aspect; int xres; int yres; int /*<<< orphan*/  gct_background; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  fz_clampi (unsigned char const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const unsigned char *
gif_read_lsd(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	if (end - p < 7)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in logical screen descriptor in gif image");

	info->width = p[1] << 8 | p[0];
	info->height = p[3] << 8 | p[2];
	if (info->width <= 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "image width must be > 0");
	if (info->height <= 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "image height must be > 0");
	if (info->height > UINT_MAX / info->width / 3 /* components */)
		fz_throw(ctx, FZ_ERROR_GENERIC, "image dimensions might overflow");

	info->has_gct = (p[4] >> 7) & 0x1;
	if (info->has_gct)
	{
		info->gct_entries = 1 << ((p[4] & 0x7) + 1);
		info->gct_background = fz_clampi(p[5], 0, info->gct_entries - 1);
	}
	info->aspect = p[6];

	info->xres = 96;
	info->yres= 96;
	if (info->aspect > 0)
		info->yres = (((float) info->aspect + 15) / 64) * 96;

	return p + 7;
}