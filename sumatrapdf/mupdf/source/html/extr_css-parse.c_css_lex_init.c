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
struct lexbuf {unsigned char const* s; char const* file; int line; scalar_t__ string_len; scalar_t__ c; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  fz_pool ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  css_lex_next (struct lexbuf*) ; 

__attribute__((used)) static void css_lex_init(fz_context *ctx, struct lexbuf *buf, fz_pool *pool, const char *s, const char *file)
{
	buf->ctx = ctx;
	buf->pool = pool;
	buf->s = (const unsigned char *)s;
	buf->c = 0;
	buf->file = file;
	buf->line = 1;
	css_lex_next(buf);

	buf->string_len = 0;
}