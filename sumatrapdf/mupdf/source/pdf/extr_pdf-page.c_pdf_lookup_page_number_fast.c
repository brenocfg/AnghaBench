#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rev_page_count; TYPE_1__* rev_page_map; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int object; int page; } ;

/* Variables and functions */

__attribute__((used)) static int
pdf_lookup_page_number_fast(fz_context *ctx, pdf_document *doc, int needle)
{
	int l = 0;
	int r = doc->rev_page_count - 1;
	while (l <= r)
	{
		int m = (l + r) >> 1;
		int c = needle - doc->rev_page_map[m].object;
		if (c < 0)
			r = m - 1;
		else if (c > 0)
			l = m + 1;
		else
			return doc->rev_page_map[m].page;
	}
	return -1;
}