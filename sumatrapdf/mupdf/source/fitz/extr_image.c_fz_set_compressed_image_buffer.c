#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {scalar_t__ get_pixmap; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buffer; TYPE_1__ super; } ;
typedef  TYPE_2__ fz_compressed_image ;
typedef  int /*<<< orphan*/  fz_compressed_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compressed_image_get_pixmap ; 

void fz_set_compressed_image_buffer(fz_context *ctx, fz_compressed_image *image, fz_compressed_buffer *buf)
{
	assert(image != NULL && image->super.get_pixmap == compressed_image_get_pixmap);
	((fz_compressed_image *)image)->buffer = buf; /* Note: compressed buffers are not reference counted */
}