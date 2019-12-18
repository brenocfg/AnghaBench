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
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_parse_page_range (int /*<<< orphan*/ *,char const*,int*,int*,int) ; 
 int /*<<< orphan*/  runpage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void runrange(fz_context *ctx, fz_document *doc, int count, const char *range)
{
	int start, end, i;

	while ((range = fz_parse_page_range(ctx, range, &start, &end, count)))
	{
		if (start < end)
			for (i = start; i <= end; ++i)
				runpage(ctx, doc, i);
		else
			for (i = start; i >= end; --i)
				runpage(ctx, doc, i);
	}
}