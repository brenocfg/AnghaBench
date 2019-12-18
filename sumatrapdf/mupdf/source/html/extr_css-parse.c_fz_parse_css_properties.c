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
struct lexbuf {int dummy; } ;
typedef  int /*<<< orphan*/  fz_pool ;
typedef  int /*<<< orphan*/  fz_css_property ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  css_lex_init (int /*<<< orphan*/ *,struct lexbuf*,int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  next (struct lexbuf*) ; 
 int /*<<< orphan*/ * parse_declaration_list (struct lexbuf*) ; 

fz_css_property *fz_parse_css_properties(fz_context *ctx, fz_pool *pool, const char *source)
{
	struct lexbuf buf;
	css_lex_init(ctx, &buf, pool, source, "<inline>");
	next(&buf);
	return parse_declaration_list(&buf);
}