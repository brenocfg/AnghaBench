#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lexbuf {char lookahead; int /*<<< orphan*/  string; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {char* data; char type; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ fz_css_value ;

/* Variables and functions */
#define  CSS_HASH 133 
 int CSS_KEYWORD ; 
#define  CSS_LENGTH 132 
#define  CSS_NUMBER 131 
#define  CSS_PERCENT 130 
#define  CSS_STRING 129 
#define  CSS_URI 128 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  expect (struct lexbuf*,char) ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 TYPE_1__* fz_new_css_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* fz_new_css_value_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* fz_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 int /*<<< orphan*/  parse_expr (struct lexbuf*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_value *parse_term(struct lexbuf *buf)
{
	fz_css_value *v;

	if (buf->lookahead == '+' || buf->lookahead == '-')
	{
		float sign = buf->lookahead == '-' ? -1 : 1;
		next(buf);
		if (buf->lookahead != CSS_NUMBER && buf->lookahead != CSS_LENGTH && buf->lookahead != CSS_PERCENT)
			fz_css_error(buf, "expected number");
		if (sign < 0)
		{
			v = fz_new_css_value_x(buf->ctx, buf->pool, buf->lookahead);
			v->data = fz_pool_alloc(buf->ctx, buf->pool, strlen(buf->string) + 2);
			v->data[0] = '-';
			strcpy(v->data + 1, buf->string);
		}
		else
		{
			v = fz_new_css_value(buf->ctx, buf->pool, buf->lookahead, buf->string);
		}
		next(buf);
		white(buf);
		return v;
	}

	if (buf->lookahead == CSS_KEYWORD)
	{
		v = fz_new_css_value(buf->ctx, buf->pool, CSS_KEYWORD, buf->string);
		next(buf);
		if (accept(buf, '('))
		{
			white(buf);
			v->type = '(';
			v->args = parse_expr(buf);
			expect(buf, ')');
		}
		white(buf);
		return v;
	}

	switch (buf->lookahead)
	{
	case CSS_HASH:
	case CSS_STRING:
	case CSS_URI:
	case CSS_NUMBER:
	case CSS_LENGTH:
	case CSS_PERCENT:
		v = fz_new_css_value(buf->ctx, buf->pool, buf->lookahead, buf->string);
		next(buf);
		white(buf);
		return v;
	}

	fz_css_error(buf, "expected value");
}