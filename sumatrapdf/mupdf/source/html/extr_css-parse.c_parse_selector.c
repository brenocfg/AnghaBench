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
struct lexbuf {char lookahead; } ;
typedef  int /*<<< orphan*/  fz_css_selector ;

/* Variables and functions */
 char EOF ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/ * parse_combinator (struct lexbuf*,char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parse_simple_selector (struct lexbuf*) ; 

__attribute__((used)) static fz_css_selector *parse_selector(struct lexbuf *buf)
{
	fz_css_selector *sel = parse_simple_selector(buf);
	for (;;)
	{
		if (accept(buf, ' '))
		{
			if (accept(buf, '+'))
				sel = parse_combinator(buf, '+', sel);
			else if (accept(buf, '>'))
				sel = parse_combinator(buf, '>', sel);
			else if (buf->lookahead != ',' && buf->lookahead != '{' && buf->lookahead != EOF)
				sel = parse_combinator(buf, ' ', sel);
			else
				break;
		}
		else if (accept(buf, '+'))
			sel = parse_combinator(buf, '+', sel);
		else if (accept(buf, '>'))
			sel = parse_combinator(buf, '>', sel);
		else
			break;
	}
	return sel;
}