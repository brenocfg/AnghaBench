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
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  tile; } ;
typedef  TYPE_1__ fz_compressed_image ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_compressed_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
drop_compressed_image(fz_context *ctx, fz_image *image_)
{
	fz_compressed_image *image = (fz_compressed_image *)image_;

	fz_drop_pixmap(ctx, image->tile);
	fz_drop_compressed_buffer(ctx, image->buffer);
}