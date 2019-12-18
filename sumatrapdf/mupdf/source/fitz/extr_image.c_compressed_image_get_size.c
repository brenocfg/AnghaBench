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
typedef  int /*<<< orphan*/  fz_pixmap_image ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {TYPE_2__* buffer; int /*<<< orphan*/  tile; } ;
typedef  TYPE_3__ fz_compressed_image ;
struct TYPE_5__ {TYPE_1__* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 size_t fz_pixmap_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
compressed_image_get_size(fz_context *ctx, fz_image *image)
{
	fz_compressed_image *im = (fz_compressed_image *)image;

	if (image == NULL)
		return 0;

	return sizeof(fz_pixmap_image) + fz_pixmap_size(ctx, im->tile) + (im->buffer && im->buffer->buffer ? im->buffer->buffer->cap : 0);
}