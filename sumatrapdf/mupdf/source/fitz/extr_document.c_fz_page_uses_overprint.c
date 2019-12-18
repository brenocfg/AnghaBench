#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* overprint ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_page ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

int fz_page_uses_overprint(fz_context *ctx, fz_page *page)
{
	if (page && page->overprint)
		return page->overprint(ctx, page);
	return 0;
}