#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  xps_drop_fixed_documents (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_drop_fixed_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xps_drop_link_targets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
xps_drop_page_list(fz_context *ctx, xps_document *doc)
{
	xps_drop_fixed_documents(ctx, doc);
	xps_drop_fixed_pages(ctx, doc);
	xps_drop_link_targets(ctx, doc);
}