#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pdf_token ;
struct TYPE_4__ {int i; int /*<<< orphan*/  len; int /*<<< orphan*/  scratch; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  pdf_cmap ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ PDF_TOK_INT ; 
 scalar_t__ PDF_TOK_KEYWORD ; 
 scalar_t__ PDF_TOK_STRING ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pdf_code_from_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_lex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pdf_map_range_to_range (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pdf_parse_cid_range(fz_context *ctx, pdf_cmap *cmap, fz_stream *file, pdf_lexbuf *buf)
{
	pdf_token tok;
	int lo, hi, dst;

	while (1)
	{
		tok = pdf_lex(ctx, file, buf);

		if (tok == PDF_TOK_KEYWORD && !strcmp(buf->scratch, "endcidrange"))
			return;

		else if (tok != PDF_TOK_STRING)
			fz_throw(ctx, FZ_ERROR_GENERIC, "expected string or endcidrange");

		lo = pdf_code_from_string(buf->scratch, buf->len);

		tok = pdf_lex(ctx, file, buf);
		if (tok != PDF_TOK_STRING)
			fz_throw(ctx, FZ_ERROR_GENERIC, "expected string");

		hi = pdf_code_from_string(buf->scratch, buf->len);

		tok = pdf_lex(ctx, file, buf);
		if (tok != PDF_TOK_INT)
			fz_throw(ctx, FZ_ERROR_GENERIC, "expected integer");

		dst = buf->i;

		pdf_map_range_to_range(ctx, cmap, lo, hi, dst);
	}
}