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
struct lexbuf {scalar_t__ lookahead; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; int /*<<< orphan*/ * string; } ;
struct TYPE_4__ {void* cond; } ;
typedef  TYPE_1__ fz_css_selector ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 TYPE_1__* fz_new_css_selector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ iscond (scalar_t__) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 void* parse_condition_list (struct lexbuf*) ; 

__attribute__((used)) static fz_css_selector *parse_simple_selector(struct lexbuf *buf)
{
	fz_css_selector *s;

	if (accept(buf, '*'))
	{
		s = fz_new_css_selector(buf->ctx, buf->pool, NULL);
		if (iscond(buf->lookahead))
			s->cond = parse_condition_list(buf);
		return s;
	}
	else if (buf->lookahead == CSS_KEYWORD)
	{
		s = fz_new_css_selector(buf->ctx, buf->pool, buf->string);
		next(buf);
		if (iscond(buf->lookahead))
			s->cond = parse_condition_list(buf);
		return s;
	}
	else if (iscond(buf->lookahead))
	{
		s = fz_new_css_selector(buf->ctx, buf->pool, NULL);
		s->cond = parse_condition_list(buf);
		return s;
	}

	fz_css_error(buf, "expected selector");
}