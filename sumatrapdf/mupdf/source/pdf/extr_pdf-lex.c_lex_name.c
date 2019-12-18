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
struct TYPE_4__ {char* scratch; int len; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ pdf_lexbuf ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  EOF 133 
#define  IS_DELIM 132 
#define  IS_WHITE 131 
#define  RANGE_0_9 130 
#define  RANGE_A_F 129 
#define  RANGE_a_f 128 
 int fz_mini (int,int /*<<< orphan*/ ) ; 
 int fz_peek_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_unread_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 char lex_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_lexbuf_grow (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
lex_name(fz_context *ctx, fz_stream *f, pdf_lexbuf *lb)
{
	char *s = lb->scratch;
	char *e = s + fz_mini(127, lb->size);
	int c;

	while (1)
	{
		if (s == e)
		{
			if (e - lb->scratch < 127)
			{
				s += pdf_lexbuf_grow(ctx, lb);
				e = lb->scratch + fz_mini(127, lb->size);
			}
			else
			{
				/* truncate names that are too long */
				fz_warn(ctx, "name is too long");
				*s = 0;
				lb->len = s - lb->scratch;
				s = NULL;
			}
		}
		c = lex_byte(ctx, f);
		switch (c)
		{
		case IS_WHITE:
		case IS_DELIM:
			fz_unread_byte(ctx, f);
			goto end;
		case EOF:
			goto end;
		case '#':
		{
			int hex[2];
			int i;
			for (i = 0; i < 2; i++)
			{
				c = fz_peek_byte(ctx, f);
				switch (c)
				{
				case RANGE_0_9:
					if (i == 1 && c == '0' && hex[0] == 0)
						goto illegal;
					hex[i] = lex_byte(ctx, f) - '0';
					break;
				case RANGE_a_f:
					hex[i] = lex_byte(ctx, f) - 'a' + 10;
					break;
				case RANGE_A_F:
					hex[i] = lex_byte(ctx, f) - 'A' + 10;
					break;
				default:
				case EOF:
					goto illegal;
				}
			}
			if (s) *s++ = (hex[0] << 4) + hex[1];
			break;
illegal:
			if (i == 1)
				fz_unread_byte(ctx, f);
			if (s) *s++ = '#';
			continue;
		}
		default:
			if (s) *s++ = c;
			break;
		}
	}
end:
	if (s)
	{
		*s = '\0';
		lb->len = s - lb->scratch;
	}
}