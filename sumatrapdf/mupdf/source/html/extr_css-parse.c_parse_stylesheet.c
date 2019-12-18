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
struct lexbuf {scalar_t__ lookahead; int /*<<< orphan*/  string; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ fz_css_rule ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 scalar_t__ EOF ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 TYPE_1__* parse_at_font_face (struct lexbuf*) ; 
 TYPE_1__* parse_at_page (struct lexbuf*) ; 
 int /*<<< orphan*/  parse_at_rule (struct lexbuf*) ; 
 TYPE_1__* parse_ruleset (struct lexbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_rule *parse_stylesheet(struct lexbuf *buf, fz_css_rule *chain)
{
	fz_css_rule *rule, **nextp, *tail;

	tail = chain;
	if (tail)
	{
		while (tail->next)
			tail = tail->next;
		nextp = &tail->next;
	}
	else
	{
		nextp = &tail;
	}

	white(buf);

	while (buf->lookahead != EOF)
	{
		if (accept(buf, '@'))
		{
			if (buf->lookahead == CSS_KEYWORD && !strcmp(buf->string, "page"))
			{
				next(buf);
				rule = *nextp = parse_at_page(buf);
				nextp = &rule->next;
			}
			else if (buf->lookahead == CSS_KEYWORD && !strcmp(buf->string, "font-face"))
			{
				next(buf);
				rule = *nextp = parse_at_font_face(buf);
				nextp = &rule->next;
			}
			else
			{
				parse_at_rule(buf);
			}
		}
		else
		{
			fz_css_rule *x = parse_ruleset(buf);
			if (x)
			{
				rule = *nextp = x;
				nextp = &rule->next;
			}
		}
		white(buf);
	}

	return chain ? chain : tail;
}