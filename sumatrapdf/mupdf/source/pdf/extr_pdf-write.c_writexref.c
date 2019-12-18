#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  out; int /*<<< orphan*/  do_ascii; int /*<<< orphan*/  do_tight; scalar_t__ do_incremental; int /*<<< orphan*/  first_xref_entry_offset; } ;
typedef  TYPE_1__ pdf_write_state ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_11__ {int startxref; scalar_t__ has_xref_streams; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Encrypt ; 
 int /*<<< orphan*/  ID ; 
 int /*<<< orphan*/  Info ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Prev ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  Size ; 
 int /*<<< orphan*/  fz_tell_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_var (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_drop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_put_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_keep_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_new_dict (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * pdf_new_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_print_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_trailer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ pdf_xref_is_incremental (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  writexrefsubsect (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

__attribute__((used)) static void writexref(fz_context *ctx, pdf_document *doc, pdf_write_state *opts, int from, int to, int first, int64_t main_xref_offset, int64_t startxref)
{
	pdf_obj *trailer = NULL;
	pdf_obj *obj;
	pdf_obj *nobj = NULL;

	fz_write_string(ctx, opts->out, "xref\n");
	opts->first_xref_entry_offset = fz_tell_output(ctx, opts->out);

	if (opts->do_incremental)
	{
		int subfrom = from;
		int subto;

		while (subfrom < to)
		{
			while (subfrom < to && !pdf_xref_is_incremental(ctx, doc, subfrom))
				subfrom++;

			subto = subfrom;
			while (subto < to && pdf_xref_is_incremental(ctx, doc, subto))
				subto++;

			if (subfrom < subto)
				writexrefsubsect(ctx, opts, subfrom, subto);

			subfrom = subto;
		}
	}
	else
	{
		writexrefsubsect(ctx, opts, from, to);
	}

	fz_write_string(ctx, opts->out, "\n");

	fz_var(trailer);

	if (opts->do_incremental)
	{
		trailer = pdf_keep_obj(ctx, pdf_trailer(ctx, doc));
		pdf_dict_put_int(ctx, trailer, PDF_NAME(Size), pdf_xref_len(ctx, doc));
		pdf_dict_put_int(ctx, trailer, PDF_NAME(Prev), doc->startxref);
		doc->startxref = startxref;
	}
	else
	{
		trailer = pdf_new_dict(ctx, doc, 5);

		nobj = pdf_new_int(ctx, to);
		pdf_dict_put_drop(ctx, trailer, PDF_NAME(Size), nobj);

		if (first)
		{
			obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Info));
			if (obj)
				pdf_dict_put(ctx, trailer, PDF_NAME(Info), obj);

			obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Root));
			if (obj)
				pdf_dict_put(ctx, trailer, PDF_NAME(Root), obj);

			obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(ID));
			if (obj)
				pdf_dict_put(ctx, trailer, PDF_NAME(ID), obj);

			obj = pdf_dict_get(ctx, pdf_trailer(ctx, doc), PDF_NAME(Encrypt));
			if (obj)
				pdf_dict_put(ctx, trailer, PDF_NAME(Encrypt), obj);
		}
		if (main_xref_offset != 0)
		{
			nobj = pdf_new_int(ctx, main_xref_offset);
			pdf_dict_put_drop(ctx, trailer, PDF_NAME(Prev), nobj);
		}
	}

	fz_write_string(ctx, opts->out, "trailer\n");
	/* Trailer is NOT encrypted */
	pdf_print_obj(ctx, opts->out, trailer, opts->do_tight, opts->do_ascii);
	fz_write_string(ctx, opts->out, "\n");

	pdf_drop_obj(ctx, trailer);

	fz_write_printf(ctx, opts->out, "startxref\n%lu\n%%%%EOF\n", startxref);

	doc->has_xref_streams = 0;
}