#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct genstate {int at_bol; int emit_white; size_t last_brk_cls; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_17__ {scalar_t__ type; struct TYPE_17__* up; TYPE_1__* style; } ;
typedef  TYPE_2__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_16__ {int white_space; } ;

/* Variables and functions */
 scalar_t__ BOX_FLOW ; 
 int UCDN_LINEBREAK_CLASS_RI ; 
 void* UCDN_LINEBREAK_CLASS_WJ ; 
 int WS_ALLOW_BREAK_SPACE ; 
 int WS_COLLAPSE ; 
 int WS_FORCE_BREAK_NEWLINE ; 
 int /*<<< orphan*/  add_flow_break (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_flow_sbreak (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_flow_shyphen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_flow_space (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_flow_word (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,char const*,char const*,int) ; 
 int /*<<< orphan*/  flush_space (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int,struct genstate*) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 scalar_t__ iswhite (char const) ; 
 int** pairbrk ; 
 int ucdn_get_resolved_linebreak_class (int) ; 

__attribute__((used)) static void generate_text(fz_context *ctx, fz_html_box *box, const char *text, int lang, struct genstate *g)
{
	fz_html_box *flow;
	fz_pool *pool = g->pool;
	int collapse = box->style->white_space & WS_COLLAPSE;
	int bsp = box->style->white_space & WS_ALLOW_BREAK_SPACE;
	int bnl = box->style->white_space & WS_FORCE_BREAK_NEWLINE;

	static const char *space = " ";

	flow = box;
	while (flow->type != BOX_FLOW)
		flow = flow->up;

	while (*text)
	{
		if (bnl && (*text == '\n' || *text == '\r'))
		{
			if (text[0] == '\r' && text[1] == '\n')
				text += 2;
			else
				text += 1;
			add_flow_break(ctx, pool, flow, box);
			g->at_bol = 1;
		}
		else if (iswhite(*text))
		{
			if (collapse)
			{
				if (bnl)
					while (*text == ' ' || *text == '\t')
						++text;
				else
					while (iswhite(*text))
						++text;
				g->emit_white = 1;
			}
			else
			{
				// TODO: tabs
				if (bsp)
					add_flow_space(ctx, pool, flow, box);
				else
					add_flow_word(ctx, pool, flow, box, space, space+1, lang);
				++text;
			}
			g->last_brk_cls = UCDN_LINEBREAK_CLASS_WJ; /* don't add sbreaks after a space */
		}
		else
		{
			const char *prev, *mark = text;
			int c;

			flush_space(ctx, flow, box, lang, g);

			if (g->at_bol)
				g->last_brk_cls = UCDN_LINEBREAK_CLASS_WJ;

			while (*text && !iswhite(*text))
			{
				prev = text;
				text += fz_chartorune(&c, text);
				if (c == 0xAD) /* soft hyphen */
				{
					if (mark != prev)
						add_flow_word(ctx, pool, flow, box, mark, prev, lang);
					add_flow_shyphen(ctx, pool, flow, box);
					mark = text;
					g->last_brk_cls = UCDN_LINEBREAK_CLASS_WJ; /* don't add sbreaks after a soft hyphen */
				}
				else if (bsp) /* allow soft breaks */
				{
					int this_brk_cls = ucdn_get_resolved_linebreak_class(c);
					if (this_brk_cls < UCDN_LINEBREAK_CLASS_RI)
					{
						int brk = pairbrk[g->last_brk_cls][this_brk_cls];

						/* we handle spaces elsewhere, so ignore these classes */
						if (brk == '@') brk = '^';
						if (brk == '#') brk = '^';
						if (brk == '%') brk = '^';

						if (brk == '_')
						{
							if (mark != prev)
								add_flow_word(ctx, pool, flow, box, mark, prev, lang);
							add_flow_sbreak(ctx, pool, flow, box);
							mark = prev;
						}

						g->last_brk_cls = this_brk_cls;
					}
				}
			}
			if (mark != text)
				add_flow_word(ctx, pool, flow, box, mark, text, lang);

			g->at_bol = 0;
		}
	}
}