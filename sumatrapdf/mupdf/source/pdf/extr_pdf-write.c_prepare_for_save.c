#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  do_ascii; scalar_t__ do_sanitize; scalar_t__ do_clean; } ;
typedef  TYPE_1__ pdf_write_options ;
struct TYPE_8__ {int save_in_progress; } ;
typedef  TYPE_2__ pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  clean_content_streams (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  presize_unsaved_signature_byteranges (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
prepare_for_save(fz_context *ctx, pdf_document *doc, pdf_write_options *in_opts)
{
	/* Rewrite (and possibly sanitize) the operator streams */
	if (in_opts->do_clean || in_opts->do_sanitize)
		clean_content_streams(ctx, doc, in_opts->do_sanitize, in_opts->do_ascii);

	/* When saving a PDF with signatures the file will
	first be written once, then the file will have its
	digests and byte ranges calculated and and then the
	signature dictionary containing them will be updated
	both in memory and in the saved file. By setting this
	flag we avoid a new xref section from being created when
	the signature dictionary is updated. */
	doc->save_in_progress = 1;

	presize_unsaved_signature_byteranges(ctx, doc);
}