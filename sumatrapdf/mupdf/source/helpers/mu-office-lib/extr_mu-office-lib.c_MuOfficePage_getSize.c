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
struct TYPE_6__ {int x1; int x0; int y1; int y0; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  page; TYPE_3__* doc; } ;
typedef  TYPE_2__ MuOfficePage ;
typedef  TYPE_3__ MuOfficeDoc ;
typedef  int /*<<< orphan*/  MuError ;

/* Variables and functions */
 int /*<<< orphan*/  MuError_BadNull ; 
 int /*<<< orphan*/  MuError_OK ; 
 TYPE_1__ fz_bound_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MuError MuOfficePage_getSize(	MuOfficePage *page,
				float        *pWidth,
				float        *pHeight)
{
	MuOfficeDoc *doc;
	fz_rect rect;

	if (!page)
		return MuError_BadNull;
	doc = page->doc;
	if (!doc)
		return MuError_BadNull;

	rect = fz_bound_page(doc->ctx, page->page);

	/* MuPDF measures in points (72ths of an inch). This API wants
	 * 90ths of an inch, so adjust. */

	if (pWidth)
		*pWidth = 90 * (rect.x1 - rect.x0) / 72;
	if (pHeight)
		*pHeight = 90 * (rect.y1 - rect.y0) / 72;

	return MuError_OK;
}