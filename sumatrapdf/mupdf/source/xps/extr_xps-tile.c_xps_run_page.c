#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* doc; } ;
typedef  TYPE_1__ xps_page ;
struct TYPE_6__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * cookie; } ;
typedef  TYPE_2__ xps_document ;
typedef  int /*<<< orphan*/  fz_page ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_cookie ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_pre_scale (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  xps_parse_fixed_page (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
xps_run_page(fz_context *ctx, fz_page *page_, fz_device *dev, fz_matrix ctm, fz_cookie *cookie)
{
	xps_page *page = (xps_page*)page_;
	xps_document *doc = page->doc;
	fz_matrix page_ctm;

	page_ctm = fz_pre_scale(ctm, 72.0f / 96.0f, 72.0f / 96.0f);

	doc->cookie = cookie;
	doc->dev = dev;
	xps_parse_fixed_page(ctx, doc, page_ctm, page);
	doc->cookie = NULL;
	doc->dev = NULL;
}