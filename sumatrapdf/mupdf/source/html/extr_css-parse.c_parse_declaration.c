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
struct lexbuf {scalar_t__ lookahead; int /*<<< orphan*/  string; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int important; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ fz_css_property ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  expect (struct lexbuf*,char) ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 TYPE_1__* fz_new_css_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 int /*<<< orphan*/  parse_expr (struct lexbuf*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_property *parse_declaration(struct lexbuf *buf)
{
	fz_css_property *p;

	if (buf->lookahead != CSS_KEYWORD)
		fz_css_error(buf, "expected keyword in property");
	p = fz_new_css_property(buf->ctx, buf->pool, buf->string, NULL, 0);
	next(buf);

	white(buf);
	expect(buf, ':');
	white(buf);

	p->value = parse_expr(buf);

	/* !important */
	if (accept(buf, '!'))
	{
		white(buf);
		if (buf->lookahead != CSS_KEYWORD || strcmp(buf->string, "important"))
			fz_css_error(buf, "expected keyword 'important' after '!'");
		p->important = 1;
		next(buf);
		white(buf);
	}

	return p;
}