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
struct lexbuf {scalar_t__ lookahead; int /*<<< orphan*/  string; int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 scalar_t__ CSS_KEYWORD ; 
 scalar_t__ CSS_STRING ; 
 int /*<<< orphan*/  fz_css_error (struct lexbuf*,char*) ; 
 char* fz_pool_strdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static char *parse_attrib_value(struct lexbuf *buf)
{
	char *s;

	if (buf->lookahead == CSS_KEYWORD || buf->lookahead == CSS_STRING)
	{
		s = fz_pool_strdup(buf->ctx, buf->pool, buf->string);
		next(buf);
		white(buf);
		return s;
	}

	fz_css_error(buf, "expected attribute value");
}