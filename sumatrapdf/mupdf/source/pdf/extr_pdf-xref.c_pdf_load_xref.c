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
struct TYPE_10__ {float type; int gen; scalar_t__ ofs; scalar_t__ num; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_lexbuf ;
struct TYPE_11__ {scalar_t__ file_size; int /*<<< orphan*/  startxref; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* pdf_get_xref_entry (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  pdf_prime_xref_index (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_read_start_xref (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pdf_read_xref_sections (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
pdf_load_xref(fz_context *ctx, pdf_document *doc, pdf_lexbuf *buf)
{
	int i;
	int xref_len;
	pdf_xref_entry *entry;

	pdf_read_start_xref(ctx, doc);

	pdf_read_xref_sections(ctx, doc, doc->startxref, buf, 1);

	if (pdf_xref_len(ctx, doc) == 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "found xref was empty");

	pdf_prime_xref_index(ctx, doc);

	entry = pdf_get_xref_entry(ctx, doc, 0);
	/* broken pdfs where first object is missing */
	if (!entry->type)
	{
		entry->type = 'f';
		entry->gen = 65535;
		entry->num = 0;
	}
	/* broken pdfs where first object is not free */
	else if (entry->type != 'f')
		fz_warn(ctx, "first object in xref is not free");

	/* broken pdfs where object offsets are out of range */
	xref_len = pdf_xref_len(ctx, doc);
	for (i = 0; i < xref_len; i++)
	{
		entry = pdf_get_xref_entry(ctx, doc, i);
		if (entry->type == 'n')
		{
			/* Special case code: "0000000000 * n" means free,
			 * according to some producers (inc Quartz) */
			if (entry->ofs == 0)
				entry->type = 'f';
			else if (entry->ofs <= 0 || entry->ofs >= doc->file_size)
				fz_throw(ctx, FZ_ERROR_GENERIC, "object offset out of range: %d (%d 0 R)", (int)entry->ofs, i);
		}
		if (entry->type == 'o')
		{
			/* Read this into a local variable here, because pdf_get_xref_entry
			 * may solidify the xref, hence invalidating "entry", meaning we
			 * need a stashed value for the throw. */
			int64_t ofs = entry->ofs;
			if (ofs <= 0 || ofs >= xref_len || pdf_get_xref_entry(ctx, doc, ofs)->type != 'n')
				fz_throw(ctx, FZ_ERROR_GENERIC, "invalid reference to an objstm that does not exist: %d (%d 0 R)", (int)ofs, i);
		}
	}
}