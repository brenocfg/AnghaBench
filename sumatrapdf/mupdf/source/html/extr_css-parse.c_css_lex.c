#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lexbuf {char c; scalar_t__ string_len; } ;

/* Variables and functions */
 int CSS_URI ; 
 int EOF ; 
 scalar_t__ css_lex_accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  css_lex_expect (struct lexbuf*,char) ; 
 int css_lex_hash (struct lexbuf*) ; 
 int css_lex_keyword (struct lexbuf*) ; 
 int /*<<< orphan*/  css_lex_next (struct lexbuf*) ; 
 int css_lex_number (struct lexbuf*) ; 
 int css_lex_string (struct lexbuf*,char) ; 
 int /*<<< orphan*/  css_lex_uri (struct lexbuf*) ; 
 int /*<<< orphan*/  css_push_char (struct lexbuf*,unsigned char) ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 scalar_t__ isnmchar (char) ; 
 scalar_t__ isnmstart (char) ; 
 scalar_t__ iswhite (char) ; 

__attribute__((used)) static int css_lex(struct lexbuf *buf)
{
	int t;

	// TODO: keyword escape sequences

	buf->string_len = 0;

restart:
	if (buf->c == 0)
		return EOF;

	if (iswhite(buf->c))
	{
		while (iswhite(buf->c))
			css_lex_next(buf);
		return ' ';
	}

	if (css_lex_accept(buf, '/'))
	{
		if (css_lex_accept(buf, '*'))
		{
			while (buf->c)
			{
				if (css_lex_accept(buf, '*'))
				{
					while (buf->c == '*')
						css_lex_next(buf);
					if (css_lex_accept(buf, '/'))
						goto restart;
				}
				css_lex_next(buf);
			}
			fz_css_error(buf, "unterminated comment");
		}
		return '/';
	}

	if (css_lex_accept(buf, '<'))
	{
		if (css_lex_accept(buf, '!'))
		{
			css_lex_expect(buf, '-');
			css_lex_expect(buf, '-');
			goto restart; /* ignore CDO */
		}
		return '<';
	}

	if (css_lex_accept(buf, '-'))
	{
		if (css_lex_accept(buf, '-'))
		{
			css_lex_expect(buf, '>');
			goto restart; /* ignore CDC */
		}
		if (isnmstart(buf->c))
		{
			css_push_char(buf, '-');
			return css_lex_keyword(buf);
		}
		return '-';
	}

	if (css_lex_accept(buf, '.'))
	{
		if (buf->c >= '0' && buf->c <= '9')
		{
			css_push_char(buf, '.');
			return css_lex_number(buf);
		}
		return '.';
	}

	if (css_lex_accept(buf, '#'))
	{
		if (isnmchar(buf->c))
			return css_lex_hash(buf);
		return '#';
	}

	if (css_lex_accept(buf, '"'))
		return css_lex_string(buf, '"');
	if (css_lex_accept(buf, '\''))
		return css_lex_string(buf, '\'');

	if (buf->c >= '0' && buf->c <= '9')
		return css_lex_number(buf);

	if (css_lex_accept(buf, 'u'))
	{
		if (css_lex_accept(buf, 'r'))
		{
			if (css_lex_accept(buf, 'l'))
			{
				if (css_lex_accept(buf, '('))
				{
					while (iswhite(buf->c))
						css_lex_next(buf);
					if (css_lex_accept(buf, '"'))
						css_lex_string(buf, '"');
					else if (css_lex_accept(buf, '\''))
						css_lex_string(buf, '\'');
					else
						css_lex_uri(buf);
					while (iswhite(buf->c))
						css_lex_next(buf);
					css_lex_expect(buf, ')');
					return CSS_URI;
				}
				css_push_char(buf, 'u');
				css_push_char(buf, 'r');
				css_push_char(buf, 'l');
				return css_lex_keyword(buf);
			}
			css_push_char(buf, 'u');
			css_push_char(buf, 'r');
			return css_lex_keyword(buf);
		}
		css_push_char(buf, 'u');
		return css_lex_keyword(buf);
	}

	if (isnmstart(buf->c))
	{
		css_push_char(buf, buf->c);
		css_lex_next(buf);
		return css_lex_keyword(buf);
	}

	t = buf->c;
	css_lex_next(buf);
	return t;
}