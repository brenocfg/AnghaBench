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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dest_is_valid_page(fz_context *ctx, pdf_obj *obj, int *page_object_nums, int pagecount)
{
	int i;
	int num = pdf_to_num(ctx, obj);

	if (num == 0)
		return 0;
	for (i = 0; i < pagecount; i++)
	{
		if (page_object_nums[i] == num)
			return 1;
	}
	return 0;
}