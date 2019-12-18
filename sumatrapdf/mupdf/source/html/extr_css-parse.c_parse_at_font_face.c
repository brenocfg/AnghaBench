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
struct lexbuf {int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  fz_css_selector ;
typedef  int /*<<< orphan*/  fz_css_rule ;
typedef  int /*<<< orphan*/  fz_css_property ;

/* Variables and functions */
 int /*<<< orphan*/  expect (struct lexbuf*,char) ; 
 int /*<<< orphan*/ * fz_new_css_rule (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_new_css_selector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * parse_declaration_list (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_rule *parse_at_font_face(struct lexbuf *buf)
{
	fz_css_selector *s = NULL;
	fz_css_property *p = NULL;

	white(buf);
	expect(buf, '{');
	p = parse_declaration_list(buf);
	expect(buf, '}');
	white(buf);

	s = fz_new_css_selector(buf->ctx, buf->pool, "@font-face");
	return fz_new_css_rule(buf->ctx, buf->pool, s, p);
}