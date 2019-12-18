#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tile; } ;
typedef  TYPE_1__ fz_pixmap_image ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_keep_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_pixmap *
pixmap_image_get_pixmap(fz_context *ctx, fz_image *image_, fz_irect *subarea, int w, int h, int *l2factor)
{
	fz_pixmap_image *image = (fz_pixmap_image *)image_;

	/* 'Simple' images created direct from pixmaps will have no buffer
	 * of compressed data. We cannot do any better than just returning
	 * a pointer to the original 'tile'.
	 */
	return fz_keep_pixmap(ctx, image->tile); /* That's all we can give you! */
}