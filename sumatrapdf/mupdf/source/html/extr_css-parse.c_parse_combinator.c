#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lexbuf {int /*<<< orphan*/  pool; int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {int combine; struct TYPE_6__* right; struct TYPE_6__* left; } ;
typedef  TYPE_1__ fz_css_selector ;

/* Variables and functions */
 TYPE_1__* fz_new_css_selector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* parse_simple_selector (struct lexbuf*) ; 
 int /*<<< orphan*/  white (struct lexbuf*) ; 

__attribute__((used)) static fz_css_selector *parse_combinator(struct lexbuf *buf, int c, fz_css_selector *a)
{
	fz_css_selector *sel, *b;
	white(buf);
	b = parse_simple_selector(buf);
	sel = fz_new_css_selector(buf->ctx, buf->pool, NULL);
	sel->combine = c;
	sel->left = a;
	sel->right = b;
	return sel;
}