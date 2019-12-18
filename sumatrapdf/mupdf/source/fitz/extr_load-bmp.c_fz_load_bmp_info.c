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
struct info {int width; int height; float xres; float yres; } ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;

/* Variables and functions */
 int /*<<< orphan*/  bmp_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_keep_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
fz_load_bmp_info(fz_context *ctx, const unsigned char *p, size_t total, int *wp, int *hp, int *xresp, int *yresp, fz_colorspace **cspacep)
{
	struct info bmp;

	bmp_read_image(ctx, &bmp, p, total, 1);

	*cspacep = fz_keep_colorspace(ctx, fz_device_rgb(ctx));
	*wp = bmp.width;
	*hp = bmp.height;
	*xresp = bmp.xres / (1000.0f / 25.4f);
	*yresp = bmp.yres / (1000.0f / 25.4f);
}