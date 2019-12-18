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
struct TYPE_3__ {scalar_t__ rev_page_count; int /*<<< orphan*/ * rev_page_map; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_drop_page_tree(fz_context *ctx, pdf_document *doc)
{
	fz_free(ctx, doc->rev_page_map);
	doc->rev_page_map = NULL;
	doc->rev_page_count = 0;
}