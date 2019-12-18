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
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_pixmap_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
pixmap_image_get_size(fz_context *ctx, fz_image *image)
{
	fz_pixmap_image *im = (fz_pixmap_image *)image;

	if (image == NULL)
		return 0;

	return sizeof(fz_pixmap_image) + fz_pixmap_size(ctx, im->tile);
}