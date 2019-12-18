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
struct TYPE_4__ {size_t len; size_t size; int /*<<< orphan*/ * scratch; int /*<<< orphan*/ * f; int /*<<< orphan*/ * i; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
#define  PDF_TOK_CLOSE_ARRAY 137 
#define  PDF_TOK_CLOSE_BRACE 136 
#define  PDF_TOK_CLOSE_DICT 135 
#define  PDF_TOK_INT 134 
#define  PDF_TOK_NAME 133 
#define  PDF_TOK_OPEN_ARRAY 132 
#define  PDF_TOK_OPEN_BRACE 131 
#define  PDF_TOK_OPEN_DICT 130 
#define  PDF_TOK_REAL 129 
#define  PDF_TOK_STRING 128 
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_append_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  fz_append_pdf_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pdf_lexbuf_grow (int /*<<< orphan*/ *,TYPE_1__*) ; 

void pdf_append_token(fz_context *ctx, fz_buffer *fzbuf, int tok, pdf_lexbuf *buf)
{
	switch (tok)
	{
	case PDF_TOK_NAME:
		fz_append_printf(ctx, fzbuf, "/%s", buf->scratch);
		break;
	case PDF_TOK_STRING:
		if (buf->len >= buf->size)
			pdf_lexbuf_grow(ctx, buf);
		buf->scratch[buf->len] = 0;
		fz_append_pdf_string(ctx, fzbuf, buf->scratch);
		break;
	case PDF_TOK_OPEN_DICT:
		fz_append_string(ctx, fzbuf, "<<");
		break;
	case PDF_TOK_CLOSE_DICT:
		fz_append_string(ctx, fzbuf, ">>");
		break;
	case PDF_TOK_OPEN_ARRAY:
		fz_append_byte(ctx, fzbuf, '[');
		break;
	case PDF_TOK_CLOSE_ARRAY:
		fz_append_byte(ctx, fzbuf, ']');
		break;
	case PDF_TOK_OPEN_BRACE:
		fz_append_byte(ctx, fzbuf, '{');
		break;
	case PDF_TOK_CLOSE_BRACE:
		fz_append_byte(ctx, fzbuf, '}');
		break;
	case PDF_TOK_INT:
		fz_append_printf(ctx, fzbuf, "%ld", buf->i);
		break;
	case PDF_TOK_REAL:
		fz_append_printf(ctx, fzbuf, "%g", buf->f);
		break;
	default:
		fz_append_data(ctx, fzbuf, buf->scratch, buf->len);
		break;
	}
}