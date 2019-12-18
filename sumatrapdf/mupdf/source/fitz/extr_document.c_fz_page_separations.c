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
typedef  int /*<<< orphan*/  fz_separations ;
struct TYPE_4__ {int /*<<< orphan*/ * (* separations ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_page ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_separations *
fz_page_separations(fz_context *ctx, fz_page *page)
{
	if (page && page->separations)
		return page->separations(ctx, page);
	return NULL;
}