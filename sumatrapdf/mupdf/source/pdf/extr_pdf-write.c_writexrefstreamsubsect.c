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
struct TYPE_3__ {int* ofs_list; int* gen_list; scalar_t__* use_list; } ;
typedef  TYPE_1__ pdf_write_state ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_array_push_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void writexrefstreamsubsect(fz_context *ctx, pdf_document *doc, pdf_write_state *opts, pdf_obj *index, fz_buffer *fzbuf, int from, int to)
{
	int num;

	pdf_array_push_int(ctx, index, from);
	pdf_array_push_int(ctx, index, to - from);
	for (num = from; num < to; num++)
	{
		fz_append_byte(ctx, fzbuf, opts->use_list[num] ? 1 : 0);
		fz_append_byte(ctx, fzbuf, opts->ofs_list[num]>>24);
		fz_append_byte(ctx, fzbuf, opts->ofs_list[num]>>16);
		fz_append_byte(ctx, fzbuf, opts->ofs_list[num]>>8);
		fz_append_byte(ctx, fzbuf, opts->ofs_list[num]);
		fz_append_byte(ctx, fzbuf, opts->gen_list[num]);
	}
}