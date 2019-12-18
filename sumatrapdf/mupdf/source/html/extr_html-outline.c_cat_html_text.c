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
struct outline_parser {scalar_t__ cat; } ;
struct TYPE_3__ {int /*<<< orphan*/  down; int /*<<< orphan*/  flow_head; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  cat_html_box (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cat_html_flow (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_clear_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fz_new_buffer (int /*<<< orphan*/ *,int) ; 
 char const* fz_string_from_buffer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static const char *
cat_html_text(fz_context *ctx, struct outline_parser *x, fz_html_box *box)
{
	if (!x->cat)
		x->cat = fz_new_buffer(ctx, 1024);
	else
		fz_clear_buffer(ctx, x->cat);

	cat_html_flow(ctx, x->cat, box->flow_head);
	cat_html_box(ctx, x->cat, box->down);

	return fz_string_from_buffer(ctx, x->cat);
}