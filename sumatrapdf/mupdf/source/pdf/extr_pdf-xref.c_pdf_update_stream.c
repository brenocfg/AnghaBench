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
struct TYPE_3__ {int /*<<< orphan*/  stm_buf; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeParms ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  Length ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_keep_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  pdf_dict_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pdf_get_xref_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_obj_parent_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_update_stream(fz_context *ctx, pdf_document *doc, pdf_obj *obj, fz_buffer *newbuf, int compressed)
{
	int num;
	pdf_xref_entry *x;

	if (pdf_is_indirect(ctx, obj))
		num = pdf_to_num(ctx, obj);
	else
		num = pdf_obj_parent_num(ctx, obj);
	if (num <= 0 || num >= pdf_xref_len(ctx, doc))
	{
		fz_warn(ctx, "object out of range (%d 0 R); xref size %d", num, pdf_xref_len(ctx, doc));
		return;
	}

	x = pdf_get_xref_entry(ctx, doc, num);

	fz_drop_buffer(ctx, x->stm_buf);
	x->stm_buf = fz_keep_buffer(ctx, newbuf);

	pdf_dict_put_int(ctx, obj, PDF_NAME(Length), (int)fz_buffer_storage(ctx, newbuf, NULL));
	if (!compressed)
	{
		pdf_dict_del(ctx, obj, PDF_NAME(Filter));
		pdf_dict_del(ctx, obj, PDF_NAME(DecodeParms));
	}
}