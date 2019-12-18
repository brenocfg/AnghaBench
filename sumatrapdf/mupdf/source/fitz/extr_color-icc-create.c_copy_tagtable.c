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
struct TYPE_3__ {int sig; int offset; int size; } ;
typedef  TYPE_1__ fz_icc_tag ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_int32_be (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
copy_tagtable(fz_context *ctx, fz_buffer *buf, fz_icc_tag *tag_list, int num_tags)
{
	int k;

	fz_append_int32_be(ctx, buf, num_tags);
	for (k = 0; k < num_tags; k++)
	{
		fz_append_int32_be(ctx, buf, tag_list[k].sig);
		fz_append_int32_be(ctx, buf, tag_list[k].offset);
		fz_append_int32_be(ctx, buf, tag_list[k].size);
	}
}