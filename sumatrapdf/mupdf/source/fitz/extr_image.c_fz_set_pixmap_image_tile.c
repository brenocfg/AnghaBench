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
struct TYPE_4__ {scalar_t__ get_pixmap; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tile; TYPE_1__ super; } ;
typedef  TYPE_2__ fz_pixmap_image ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pixmap_image_get_pixmap ; 

void fz_set_pixmap_image_tile(fz_context *ctx, fz_pixmap_image *image, fz_pixmap *pix)
{
	assert(image != NULL && image->super.get_pixmap == pixmap_image_get_pixmap);
	((fz_pixmap_image *)image)->tile = pix;
}