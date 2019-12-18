#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int start; scalar_t__ hintstream_len; int /*<<< orphan*/  hints_length; scalar_t__ hints_shared_offset; int /*<<< orphan*/  hints_s; scalar_t__ first_xref_entry_offset; int /*<<< orphan*/  linear_t; scalar_t__ page_count; int /*<<< orphan*/  linear_n; int /*<<< orphan*/  linear_e; scalar_t__* ofs_list; scalar_t__ main_xref_offset; TYPE_2__* page_object_lists; int /*<<< orphan*/  linear_o; int /*<<< orphan*/  linear_h1; int /*<<< orphan*/  linear_h0; scalar_t__ file_len; int /*<<< orphan*/  linear_l; } ;
typedef  TYPE_3__ pdf_write_state ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {TYPE_1__** page; } ;
struct TYPE_5__ {scalar_t__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_linearization_params(fz_context *ctx, pdf_document *doc, pdf_write_state *opts)
{
	int64_t offset;
	pdf_set_int(ctx, opts->linear_l, opts->file_len);
	/* Primary hint stream offset (of object, not stream!) */
	pdf_set_int(ctx, opts->linear_h0, opts->ofs_list[pdf_xref_len(ctx, doc)-1]);
	/* Primary hint stream length (of object, not stream!) */
	offset = (opts->start == 1 ? opts->main_xref_offset : opts->ofs_list[1] + opts->hintstream_len);
	pdf_set_int(ctx, opts->linear_h1, offset - opts->ofs_list[pdf_xref_len(ctx, doc)-1]);
	/* Object number of first pages page object (the first object of page 0) */
	pdf_set_int(ctx, opts->linear_o, opts->page_object_lists->page[0]->object[0]);
	/* Offset of end of first page (first page is followed by primary
	 * hint stream (object n-1) then remaining pages (object 1...). The
	 * primary hint stream counts as part of the first pages data, I think.
	 */
	offset = (opts->start == 1 ? opts->main_xref_offset : opts->ofs_list[1] + opts->hintstream_len);
	pdf_set_int(ctx, opts->linear_e, offset);
	/* Number of pages in document */
	pdf_set_int(ctx, opts->linear_n, opts->page_count);
	/* Offset of first entry in main xref table */
	pdf_set_int(ctx, opts->linear_t, opts->first_xref_entry_offset + opts->hintstream_len);
	/* Offset of shared objects hint table in the primary hint stream */
	pdf_set_int(ctx, opts->hints_s, opts->hints_shared_offset);
	/* Primary hint stream length */
	pdf_set_int(ctx, opts->hints_length, opts->hintstream_len);
}