#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_token ;
struct TYPE_7__ {int /*<<< orphan*/  scratch; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  EOF 130 
#define  IS_NUMBER 129 
#define  IS_WHITE 128 
 int /*<<< orphan*/  PDF_TOK_CLOSE_ARRAY ; 
 int /*<<< orphan*/  PDF_TOK_CLOSE_BRACE ; 
 int /*<<< orphan*/  PDF_TOK_CLOSE_DICT ; 
 int /*<<< orphan*/  PDF_TOK_EOF ; 
 int /*<<< orphan*/  PDF_TOK_ERROR ; 
 int /*<<< orphan*/  PDF_TOK_NAME ; 
 int /*<<< orphan*/  PDF_TOK_OPEN_ARRAY ; 
 int /*<<< orphan*/  PDF_TOK_OPEN_BRACE ; 
 int /*<<< orphan*/  PDF_TOK_OPEN_DICT ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lex_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_comment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lex_hex_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lex_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lex_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  lex_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lex_white (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_token_from_keyword (int /*<<< orphan*/ ) ; 

pdf_token
pdf_lex(fz_context *ctx, fz_stream *f, pdf_lexbuf *buf)
{
	while (1)
	{
		int c = lex_byte(ctx, f);
		switch (c)
		{
		case EOF:
			return PDF_TOK_EOF;
		case IS_WHITE:
			lex_white(ctx, f);
			break;
		case '%':
			lex_comment(ctx, f);
			break;
		case '/':
			lex_name(ctx, f, buf);
			return PDF_TOK_NAME;
		case '(':
			return lex_string(ctx, f, buf);
		case ')':
			return PDF_TOK_ERROR;
		case '<':
			c = lex_byte(ctx, f);
			if (c == '<')
				return PDF_TOK_OPEN_DICT;
			if (c != EOF)
				fz_unread_byte(ctx, f);
			return lex_hex_string(ctx, f, buf);
		case '>':
			c = lex_byte(ctx, f);
			if (c == '>')
				return PDF_TOK_CLOSE_DICT;
			if (c != EOF)
				fz_unread_byte(ctx, f);
			return PDF_TOK_ERROR;
		case '[':
			return PDF_TOK_OPEN_ARRAY;
		case ']':
			return PDF_TOK_CLOSE_ARRAY;
		case '{':
			return PDF_TOK_OPEN_BRACE;
		case '}':
			return PDF_TOK_CLOSE_BRACE;
		case IS_NUMBER:
			return lex_number(ctx, f, buf, c);
		default: /* isregular: !isdelim && !iswhite && c != EOF */
			fz_unread_byte(ctx, f);
			lex_name(ctx, f, buf);
			return pdf_token_from_keyword(buf->scratch);
		}
	}
}