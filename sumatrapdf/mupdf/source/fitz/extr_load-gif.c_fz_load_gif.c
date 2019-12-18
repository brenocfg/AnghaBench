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
struct info {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_4__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* gif_read_image (int /*<<< orphan*/ *,struct info*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

fz_pixmap *
fz_load_gif(fz_context *ctx, const unsigned char *p, size_t total)
{
	fz_pixmap *image;
	struct info gif;

	image = gif_read_image(ctx, &gif, p, total, 0);
	image->xres = gif.xres;
	image->yres = gif.yres;

	return image;
}