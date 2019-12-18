#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ xps_page ;
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_scale (float,float) ; 
 int /*<<< orphan*/  xps_load_links_in_fixed_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 

fz_link *
xps_load_links(fz_context *ctx, fz_page *page_)
{
	xps_page *page = (xps_page*)page_;
	fz_matrix ctm;
	fz_link *link = NULL;
	ctm = fz_scale(72.0f / 96.0f, 72.0f / 96.0f);
	xps_load_links_in_fixed_page(ctx, page->doc, ctm, page, &link);
	return link;
}