#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int glyph_count; int scale; TYPE_3__* glyph_pos; } ;
typedef  TYPE_4__ string_walker ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_14__ {int bidi_level; scalar_t__ w; TYPE_2__* box; int /*<<< orphan*/  markup_lang; int /*<<< orphan*/  script; int /*<<< orphan*/  h; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_5__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_12__ {scalar_t__ x_advance; } ;
struct TYPE_11__ {float em; TYPE_1__* style; } ;
struct TYPE_10__ {int /*<<< orphan*/  small_caps; int /*<<< orphan*/  font; int /*<<< orphan*/  line_height; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_from_css_number_scale (int /*<<< orphan*/ ,float) ; 
 char* get_node_text (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  init_string_walker (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ walk_string (TYPE_4__*) ; 

__attribute__((used)) static void measure_string(fz_context *ctx, fz_html_flow *node, hb_buffer_t *hb_buf)
{
	string_walker walker;
	unsigned int i;
	const char *s;
	float em;

	em = node->box->em;
	node->x = 0;
	node->y = 0;
	node->w = 0;
	node->h = fz_from_css_number_scale(node->box->style->line_height, em);

	s = get_node_text(ctx, node);
	init_string_walker(ctx, &walker, hb_buf, node->bidi_level & 1, node->box->style->font, node->script, node->markup_lang, node->box->style->small_caps, s);
	while (walk_string(&walker))
	{
		int x = 0;
		for (i = 0; i < walker.glyph_count; i++)
			x += walker.glyph_pos[i].x_advance;
		node->w += x * em / walker.scale;
	}
}