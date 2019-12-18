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
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_2__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ cbz_page ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbz_drop_page(fz_context *ctx, fz_page *page_)
{
	cbz_page *page = (cbz_page*)page_;
	fz_drop_image(ctx, page->image);
}