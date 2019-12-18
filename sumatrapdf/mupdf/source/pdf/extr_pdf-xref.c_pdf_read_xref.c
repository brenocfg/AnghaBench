#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_lexbuf ;
struct TYPE_5__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ pdf_document ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int fz_peek_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ iswhite (int) ; 
 int /*<<< orphan*/ * pdf_read_new_xref (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_read_old_xref (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static pdf_obj *
pdf_read_xref(fz_context *ctx, pdf_document *doc, int64_t ofs, pdf_lexbuf *buf)
{
	pdf_obj *trailer;
	int c;

	fz_seek(ctx, doc->file, ofs, SEEK_SET);

	while (iswhite(fz_peek_byte(ctx, doc->file)))
		fz_read_byte(ctx, doc->file);

	c = fz_peek_byte(ctx, doc->file);
	if (c == 'x')
		trailer = pdf_read_old_xref(ctx, doc, buf);
	else if (isdigit(c))
		trailer = pdf_read_new_xref(ctx, doc, buf);
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot recognize xref format");

	return trailer;
}