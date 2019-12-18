#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_4__ {scalar_t__* text; } ;
struct TYPE_5__ {int markup_lang; TYPE_1__ content; } ;
typedef  TYPE_2__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_WORD ; 
 TYPE_2__* add_flow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 

__attribute__((used)) static void add_flow_word(fz_context *ctx, fz_pool *pool, fz_html_box *top, fz_html_box *inline_box, const char *a, const char *b, int lang)
{
	fz_html_flow *flow = add_flow(ctx, pool, top, inline_box, FLOW_WORD, b - a + 1);
	memcpy(flow->content.text, a, b - a);
	flow->content.text[b - a] = 0;
	flow->markup_lang = lang;
}