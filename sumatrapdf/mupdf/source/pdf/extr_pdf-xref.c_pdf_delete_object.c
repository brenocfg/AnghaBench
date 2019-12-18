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
struct TYPE_3__ {float type; int gen; int /*<<< orphan*/ * obj; int /*<<< orphan*/ * stm_buf; scalar_t__ stm_ofs; scalar_t__ num; scalar_t__ ofs; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pdf_get_incremental_xref_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_delete_object(fz_context *ctx, pdf_document *doc, int num)
{
	pdf_xref_entry *x;

	if (num <= 0 || num >= pdf_xref_len(ctx, doc))
	{
		fz_warn(ctx, "object out of range (%d 0 R); xref size %d", num, pdf_xref_len(ctx, doc));
		return;
	}

	x = pdf_get_incremental_xref_entry(ctx, doc, num);

	fz_drop_buffer(ctx, x->stm_buf);
	pdf_drop_obj(ctx, x->obj);

	x->type = 'f';
	x->ofs = 0;
	x->gen += 1;
	x->num = 0;
	x->stm_ofs = 0;
	x->stm_buf = NULL;
	x->obj = NULL;
}