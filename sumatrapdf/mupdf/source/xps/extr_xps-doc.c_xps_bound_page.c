#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* fix; } ;
typedef  TYPE_2__ xps_page ;
struct TYPE_7__ {float x1; float y1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_3__ fz_rect ;
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {float width; float height; } ;

/* Variables and functions */

__attribute__((used)) static fz_rect
xps_bound_page(fz_context *ctx, fz_page *page_)
{
	xps_page *page = (xps_page*)page_;
	fz_rect bounds;
	bounds.x0 = bounds.y0 = 0;
	bounds.x1 = page->fix->width * 72.0f / 96.0f;
	bounds.y1 = page->fix->height * 72.0f / 96.0f;
	return bounds;
}