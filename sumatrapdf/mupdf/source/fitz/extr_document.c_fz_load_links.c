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
struct TYPE_4__ {int /*<<< orphan*/ * (* load_links ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_page ;
typedef  int /*<<< orphan*/  fz_link ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

fz_link *
fz_load_links(fz_context *ctx, fz_page *page)
{
	if (page && page->load_links)
		return page->load_links(ctx, page);
	return NULL;
}