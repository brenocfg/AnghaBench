#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x1; int y1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_page ;
struct TYPE_7__ {int w; int h; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {TYPE_2__* image; } ;
typedef  TYPE_3__ cbz_page ;

/* Variables and functions */
 int DPI ; 
 int /*<<< orphan*/  fz_image_resolution (TYPE_2__*,int*,int*) ; 

__attribute__((used)) static fz_rect
cbz_bound_page(fz_context *ctx, fz_page *page_)
{
	cbz_page *page = (cbz_page*)page_;
	fz_image *image = page->image;
	int xres, yres;
	fz_rect bbox;

	fz_image_resolution(image, &xres, &yres);
	bbox.x0 = bbox.y0 = 0;
	bbox.x1 = image->w * DPI / xres;
	bbox.y1 = image->h * DPI / yres;
	return bbox;
}