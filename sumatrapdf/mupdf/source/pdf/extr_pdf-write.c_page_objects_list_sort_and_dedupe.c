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
struct TYPE_3__ {int len; int /*<<< orphan*/ * page; } ;
typedef  TYPE_1__ page_objects_list ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  page_objects_dedupe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_objects_sort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
page_objects_list_sort_and_dedupe(fz_context *ctx, page_objects_list *pol)
{
	int i;
	int n = pol->len;

	for (i = 0; i < n; i++)
	{
		page_objects_sort(ctx, pol->page[i]);
		page_objects_dedupe(ctx, pol->page[i]);
	}
}