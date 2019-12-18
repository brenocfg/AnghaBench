#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct genstate {scalar_t__ emit_white; int /*<<< orphan*/  at_bol; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_10__ {TYPE_1__* style; } ;
typedef  TYPE_2__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {int white_space; } ;

/* Variables and functions */
 int WS_ALLOW_BREAK_SPACE ; 
 int /*<<< orphan*/  add_flow_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_flow_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,char const*,char const*,int) ; 

__attribute__((used)) static void flush_space(fz_context *ctx, fz_html_box *flow, fz_html_box *inline_box, int lang, struct genstate *g)
{
	static const char *space = " ";
	int bsp = inline_box->style->white_space & WS_ALLOW_BREAK_SPACE;
	fz_pool *pool = g->pool;
	if (g->emit_white)
	{
		if (!g->at_bol)
		{
			if (bsp)
				add_flow_space(ctx, pool, flow, inline_box);
			else
				add_flow_word(ctx, pool, flow, inline_box, space, space+1, lang);
		}
		g->emit_white = 0;
	}
}