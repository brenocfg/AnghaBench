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
struct lexbuf {char lookahead; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;
struct TYPE_3__ {struct TYPE_3__* next; } ;
typedef  TYPE_1__ fz_css_value ;

/* Variables and functions */
 char EOF ; 
 scalar_t__ accept (struct lexbuf*,char) ; 
 void* fz_new_css_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char*) ; 
 void* parse_term (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_value *parse_expr(struct lexbuf *buf)
{
	fz_css_value *head, *tail;

	head = tail = parse_term(buf);

	while (buf->lookahead != '}' && buf->lookahead != ';' && buf->lookahead != '!' &&
			buf->lookahead != ')' && buf->lookahead != EOF)
	{
		if (accept(buf, ','))
		{
			white(buf);
			tail = tail->next = fz_new_css_value(buf->ctx, buf->pool, ',', ",");
			tail = tail->next = parse_term(buf);
		}
		else if (accept(buf, '/'))
		{
			white(buf);
			tail = tail->next = fz_new_css_value(buf->ctx, buf->pool, '/', "/");
			tail = tail->next = parse_term(buf);
		}
		else
		{
			tail = tail->next = parse_term(buf);
		}
	}

	return head;
}