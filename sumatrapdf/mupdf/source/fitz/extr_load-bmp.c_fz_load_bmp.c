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
struct info {float xres; float yres; } ;
struct TYPE_4__ {float xres; float yres; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* bmp_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

fz_pixmap *
fz_load_bmp(fz_context *ctx, const unsigned char *p, size_t total)
{
	struct info bmp;
	fz_pixmap *image;

	image = bmp_read_image(ctx, &bmp, p, total, 0);
	image->xres = bmp.xres / (1000.0f / 25.4f);
	image->yres = bmp.yres / (1000.0f / 25.4f);

	return image;
}