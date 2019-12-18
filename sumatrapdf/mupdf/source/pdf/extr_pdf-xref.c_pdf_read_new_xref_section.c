#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float type; int ofs; int gen; int num; } ;
typedef  TYPE_1__ pdf_xref_entry ;
struct TYPE_7__ {int has_xref_streams; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int PDF_MAX_OBJECT_NUMBER ; 
 scalar_t__ fz_is_eof (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pdf_xref_find_subsection (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 

__attribute__((used)) static void
pdf_read_new_xref_section(fz_context *ctx, pdf_document *doc, fz_stream *stm, int i0, int i1, int w0, int w1, int w2)
{
	pdf_xref_entry *table;
	int i, n;

	if (i0 < 0 || i0 > PDF_MAX_OBJECT_NUMBER || i1 < 0 || i1 > PDF_MAX_OBJECT_NUMBER || i0 + i1 - 1 > PDF_MAX_OBJECT_NUMBER)
		fz_throw(ctx, FZ_ERROR_GENERIC, "xref subsection object numbers are out of range");

	table = pdf_xref_find_subsection(ctx, doc, i0, i1);
	for (i = i0; i < i0 + i1; i++)
	{
		pdf_xref_entry *entry = &table[i-i0];
		int a = 0;
		int64_t b = 0;
		int c = 0;

		if (fz_is_eof(ctx, stm))
			fz_throw(ctx, FZ_ERROR_GENERIC, "truncated xref stream");

		for (n = 0; n < w0; n++)
			a = (a << 8) + fz_read_byte(ctx, stm);
		for (n = 0; n < w1; n++)
			b = (b << 8) + fz_read_byte(ctx, stm);
		for (n = 0; n < w2; n++)
			c = (c << 8) + fz_read_byte(ctx, stm);

		if (!entry->type)
		{
			int t = w0 ? a : 1;
			entry->type = t == 0 ? 'f' : t == 1 ? 'n' : t == 2 ? 'o' : 0;
			entry->ofs = w1 ? b : 0;
			entry->gen = w2 ? c : 0;
			entry->num = i;
		}
	}

	doc->has_xref_streams = 1;
}