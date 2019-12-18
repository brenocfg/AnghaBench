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
struct TYPE_6__ {int do_tight; int /*<<< orphan*/ * rev_renumber_map; int /*<<< orphan*/ * renumber_map; int /*<<< orphan*/ * gen_list; int /*<<< orphan*/ * ofs_list; int /*<<< orphan*/ * use_list; scalar_t__ list_len; int /*<<< orphan*/  upwd_utf8; int /*<<< orphan*/  opwd_utf8; int /*<<< orphan*/  permissions; int /*<<< orphan*/  main_xref_offset; scalar_t__ start; int /*<<< orphan*/  do_encrypt; int /*<<< orphan*/  do_clean; int /*<<< orphan*/  do_linear; int /*<<< orphan*/  do_garbage; int /*<<< orphan*/  do_compress_fonts; int /*<<< orphan*/  do_compress_images; int /*<<< orphan*/  do_compress; int /*<<< orphan*/  do_expand; int /*<<< orphan*/  do_ascii; int /*<<< orphan*/  do_incremental; } ;
typedef  TYPE_1__ pdf_write_state ;
struct TYPE_7__ {int /*<<< orphan*/  upwd_utf8; int /*<<< orphan*/  opwd_utf8; int /*<<< orphan*/  permissions; int /*<<< orphan*/  do_encrypt; int /*<<< orphan*/  do_clean; int /*<<< orphan*/  do_linear; int /*<<< orphan*/  do_garbage; int /*<<< orphan*/  do_compress_fonts; int /*<<< orphan*/  do_compress_images; int /*<<< orphan*/  do_compress; int /*<<< orphan*/  do_decompress; int /*<<< orphan*/  do_pretty; int /*<<< orphan*/  do_ascii; int /*<<< orphan*/  do_incremental; } ;
typedef  TYPE_2__ pdf_write_options ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  expand_lists (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 
 int pdf_xref_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void initialise_write_state(fz_context *ctx, pdf_document *doc, const pdf_write_options *in_opts, pdf_write_state *opts)
{
	int xref_len = pdf_xref_len(ctx, doc);

	opts->do_incremental = in_opts->do_incremental;
	opts->do_ascii = in_opts->do_ascii;
	opts->do_tight = !in_opts->do_pretty;
	opts->do_expand = in_opts->do_decompress;
	opts->do_compress = in_opts->do_compress;
	opts->do_compress_images = in_opts->do_compress_images;
	opts->do_compress_fonts = in_opts->do_compress_fonts;

	opts->do_garbage = in_opts->do_garbage;
	opts->do_linear = in_opts->do_linear;
	opts->do_clean = in_opts->do_clean;
	opts->do_encrypt = in_opts->do_encrypt;
	opts->start = 0;
	opts->main_xref_offset = INT_MIN;

	opts->permissions = in_opts->permissions;
	memcpy(opts->opwd_utf8, in_opts->opwd_utf8, nelem(opts->opwd_utf8));
	memcpy(opts->upwd_utf8, in_opts->upwd_utf8, nelem(opts->upwd_utf8));

	/* We deliberately make these arrays long enough to cope with
	* 1 to n access rather than 0..n-1, and add space for 2 new
	* extra entries that may be required for linearization. */
	opts->list_len = 0;
	opts->use_list = NULL;
	opts->ofs_list = NULL;
	opts->gen_list = NULL;
	opts->renumber_map = NULL;
	opts->rev_renumber_map = NULL;

	expand_lists(ctx, opts, xref_len);
}