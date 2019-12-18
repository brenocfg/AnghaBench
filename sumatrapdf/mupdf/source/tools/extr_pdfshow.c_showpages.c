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
typedef  int /*<<< orphan*/  pdf_obj ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out ; 
 int pdf_count_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_lookup_page_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showpages(void)
{
	pdf_obj *ref;
	int i, n = pdf_count_pages(ctx, doc);
	for (i = 0; i < n; ++i)
	{
		ref = pdf_lookup_page_obj(ctx, doc, i);
		fz_write_printf(ctx, out, "page %d = %d 0 R\n", i + 1, pdf_to_num(ctx, ref));
	}
}