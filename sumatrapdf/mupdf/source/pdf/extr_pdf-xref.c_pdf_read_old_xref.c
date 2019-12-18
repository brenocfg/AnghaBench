#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int num; int ofs; int gen; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  scalar_t__ pdf_token ;
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_14__ {char* scratch; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ pdf_lexbuf ;
struct TYPE_15__ {int has_old_style_xrefs; int /*<<< orphan*/ * file; } ;
typedef  TYPE_3__ pdf_document ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int PDF_MAX_OBJECT_NUMBER ; 
 scalar_t__ PDF_TOK_OPEN_DICT ; 
 scalar_t__ PDF_TOK_TRAILER ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int fz_atoi (int /*<<< orphan*/ ) ; 
 int fz_peek_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_skip_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_skip_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_strsep (char**,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ iswhite (char) ; 
 scalar_t__ pdf_lex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * pdf_parse_dict (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* pdf_xref_find_subsection (int /*<<< orphan*/ *,TYPE_3__*,int,int) ; 
 int pdf_xref_size_from_old_trailer (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static pdf_obj *
pdf_read_old_xref(fz_context *ctx, pdf_document *doc, pdf_lexbuf *buf)
{
	int start, len, c, i, xref_len, carried;
	fz_stream *file = doc->file;
	pdf_xref_entry *table;
	pdf_token tok;
	size_t n;
	char *s, *e;

	xref_len = pdf_xref_size_from_old_trailer(ctx, doc, buf);

	fz_skip_space(ctx, doc->file);
	if (fz_skip_string(ctx, doc->file, "xref"))
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find xref marker");
	fz_skip_space(ctx, doc->file);

	while (1)
	{
		c = fz_peek_byte(ctx, file);
		if (!isdigit(c))
			break;

		fz_read_line(ctx, file, buf->scratch, buf->size);
		s = buf->scratch;
		start = fz_atoi(fz_strsep(&s, " "));
		len = fz_atoi(fz_strsep(&s, " "));

		/* broken pdfs where the section is not on a separate line */
		if (s && *s != '\0')
		{
			fz_warn(ctx, "broken xref subsection. proceeding anyway.");
			fz_seek(ctx, file, -(2 + (int)strlen(s)), SEEK_CUR);
		}

		if (start < 0 || start > PDF_MAX_OBJECT_NUMBER
				|| len < 0 || len > PDF_MAX_OBJECT_NUMBER
				|| start + len - 1 > PDF_MAX_OBJECT_NUMBER)
		{
			fz_throw(ctx, FZ_ERROR_GENERIC, "xref subsection object numbers are out of range");
		}
		/* broken pdfs where size in trailer undershoots entries in xref sections */
		if (start + len > xref_len)
		{
			fz_warn(ctx, "broken xref subsection, proceeding anyway.");
		}

		table = pdf_xref_find_subsection(ctx, doc, start, len);

		/* Xref entries SHOULD be 20 bytes long, but we see 19 byte
		 * ones more frequently than we'd like (e.g. PCLm drivers).
		 * Cope with this by 'carrying' data forward. */
		carried = 0;
		for (i = 0; i < len; i++)
		{
			pdf_xref_entry *entry = &table[i];
			n = fz_read(ctx, file, (unsigned char *) buf->scratch + carried, 20-carried);
			if (n != (size_t)(20-carried))
				fz_throw(ctx, FZ_ERROR_GENERIC, "unexpected EOF in xref table");
			n += carried;
			buf->scratch[n] = '\0';
			if (!entry->type)
			{
				s = buf->scratch;
				e = s + n;

				entry->num = start + i;

				/* broken pdfs where line start with white space */
				while (s < e && iswhite(*s))
					s++;

				if (s == e || !isdigit(*s))
					fz_throw(ctx, FZ_ERROR_GENERIC, "xref offset missing");
				while (s < e && isdigit(*s))
					entry->ofs = entry->ofs * 10 + *s++ - '0';

				while (s < e && iswhite(*s))
					s++;
				if (s == e || !isdigit(*s))
					fz_throw(ctx, FZ_ERROR_GENERIC, "xref generation number missing");
				while (s < e && isdigit(*s))
					entry->gen = entry->gen * 10 + *s++ - '0';

				while (s < e && iswhite(*s))
					s++;
				if (s == e || (*s != 'f' && *s != 'n' && *s != 'o'))
					fz_throw(ctx, FZ_ERROR_GENERIC, "unexpected xref type: 0x%x (%d %d R)", s == e ? 0 : *s, entry->num, entry->gen);
				entry->type = *s++;

				/* If the last byte of our buffer isn't an EOL (or space), carry one byte forward */
				carried = buf->scratch[19] > 32;
				if (carried)
					buf->scratch[0] = buf->scratch[19];
			}
		}
		if (carried)
			fz_unread_byte(ctx, file);
	}

	tok = pdf_lex(ctx, file, buf);
	if (tok != PDF_TOK_TRAILER)
		fz_throw(ctx, FZ_ERROR_GENERIC, "expected trailer marker");

	tok = pdf_lex(ctx, file, buf);
	if (tok != PDF_TOK_OPEN_DICT)
		fz_throw(ctx, FZ_ERROR_GENERIC, "expected trailer dictionary");

	doc->has_old_style_xrefs = 1;

	return pdf_parse_dict(ctx, doc, file, buf);
}