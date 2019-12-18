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
struct lexbuf {scalar_t__ lookahead; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSS_KEYWORD ; 
 scalar_t__ EOF ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  expect (struct lexbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static void parse_at_rule(struct lexbuf *buf)
{
	expect(buf, CSS_KEYWORD);

	/* skip until '{' or ';' */
	while (buf->lookahead != EOF)
	{
		if (accept(buf, ';'))
		{
			white(buf);
			return;
		}
		if (accept(buf, '{'))
		{
			int depth = 1;
			while (buf->lookahead != EOF && depth > 0)
			{
				if (accept(buf, '{'))
					++depth;
				else if (accept(buf, '}'))
					--depth;
				else
					next(buf);
			}
			white(buf);
			return;
		}
		next(buf);
	}
}