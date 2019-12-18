#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* scratch; int size; int /*<<< orphan*/  i; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  EOF 131 
#define  IS_DELIM 130 
#define  IS_WHITE 129 
 int PDF_TOK_ERROR ; 
 int PDF_TOK_INT ; 
 int PDF_TOK_REAL ; 
#define  RANGE_0_9 128 
 int /*<<< orphan*/  acrobat_compatible_atof (char*) ; 
 int /*<<< orphan*/  fast_atoi (char*) ; 
 int /*<<< orphan*/  fz_atof (char*) ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lex_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lex_number(fz_context *ctx, fz_stream *f, pdf_lexbuf *buf, int c)
{
	char *s = buf->scratch;
	char *e = buf->scratch + buf->size - 1; /* leave space for zero terminator */
	char *isreal = (c == '.' ? s : NULL);
	int neg = (c == '-');
	int isbad = 0;

	*s++ = c;

	c = lex_byte(ctx, f);

	/* skip extra '-' signs at start of number */
	if (neg)
	{
		while (c == '-')
			c = lex_byte(ctx, f);
	}

	while (s < e)
	{
		switch (c)
		{
		case IS_WHITE:
		case IS_DELIM:
			fz_unread_byte(ctx, f);
			goto end;
		case EOF:
			goto end;
		case '.':
			if (isreal)
				isbad = 1;
			isreal = s;
			*s++ = c;
			break;
		case RANGE_0_9:
			*s++ = c;
			break;
		default:
			isbad = 1;
			*s++ = c;
			break;
		}
		c = lex_byte(ctx, f);
	}

end:
	*s = '\0';
	if (isbad)
		return PDF_TOK_ERROR;
	if (isreal)
	{
		/* We'd like to use the fastest possible atof
		 * routine, but we'd rather match acrobats
		 * handling of broken numbers. As such, we
		 * spot common broken cases and call an
		 * acrobat compatible routine where required. */
		if (neg > 1 || isreal - buf->scratch >= 10)
			buf->f = acrobat_compatible_atof(buf->scratch);
		else
			buf->f = fz_atof(buf->scratch);
		return PDF_TOK_REAL;
	}
	else
	{
		buf->i = fast_atoi(buf->scratch);
		return PDF_TOK_INT;
	}
}