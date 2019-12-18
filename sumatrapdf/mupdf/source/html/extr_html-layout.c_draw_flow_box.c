#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_29__ {float scale; unsigned int glyph_count; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  font; TYPE_2__* glyph_info; TYPE_1__* glyph_pos; } ;
typedef  TYPE_6__ string_walker ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  fz_text ;
struct TYPE_30__ {float a; float d; float e; float f; scalar_t__ c; scalar_t__ b; } ;
typedef  TYPE_7__ fz_matrix ;
struct TYPE_26__ {int /*<<< orphan*/  image; } ;
struct TYPE_31__ {scalar_t__ type; float y; float h; int bidi_level; float x; float w; TYPE_3__ content; int /*<<< orphan*/  markup_lang; TYPE_4__* box; int /*<<< orphan*/  script; scalar_t__ breaks_line; struct TYPE_31__* next; } ;
typedef  TYPE_8__ fz_html_flow ;
struct TYPE_32__ {int /*<<< orphan*/  markup_dir; TYPE_8__* flow_head; } ;
typedef  TYPE_9__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_device ;
struct TYPE_28__ {float r; float g; float b; } ;
struct TYPE_23__ {scalar_t__ visibility; int /*<<< orphan*/  small_caps; int /*<<< orphan*/  font; TYPE_5__ color; } ;
typedef  TYPE_10__ fz_css_style ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_27__ {float em; TYPE_10__* style; } ;
struct TYPE_25__ {scalar_t__ cluster; int codepoint; } ;
struct TYPE_24__ {int x_offset; int y_offset; scalar_t__ y_advance; scalar_t__ x_advance; } ;

/* Variables and functions */
 scalar_t__ FLOW_IMAGE ; 
 scalar_t__ FLOW_SHYPHEN ; 
 scalar_t__ FLOW_SPACE ; 
 scalar_t__ FLOW_WORD ; 
 scalar_t__ V_VISIBLE ; 
 int fz_chartorune (int*,scalar_t__) ; 
 int /*<<< orphan*/  fz_default_color_params ; 
 int /*<<< orphan*/  fz_device_rgb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_fill_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_fill_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_7__,int /*<<< orphan*/ ,float*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fz_new_text (int /*<<< orphan*/ *) ; 
 TYPE_7__ fz_pre_scale (TYPE_7__,float,float) ; 
 TYPE_7__ fz_pre_translate (TYPE_7__,float,float) ; 
 int /*<<< orphan*/  fz_show_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* get_node_text (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  init_string_walker (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ walk_string (TYPE_6__*) ; 

__attribute__((used)) static void draw_flow_box(fz_context *ctx, fz_html_box *box, float page_top, float page_bot, fz_device *dev, fz_matrix ctm, hb_buffer_t *hb_buf)
{
	fz_html_flow *node;
	fz_text *text;
	fz_matrix trm;
	float color[3];
	float prev_color[3];

	/* FIXME: HB_DIRECTION_TTB? */

	text = NULL;
	prev_color[0] = 0;
	prev_color[1] = 0;
	prev_color[2] = 0;

	for (node = box->flow_head; node; node = node->next)
	{
		const fz_css_style *style = node->box->style;

		if (node->type == FLOW_IMAGE)
		{
			if (node->y >= page_bot || node->y + node->h <= page_top)
				continue;
		}
		else
		{
			if (node->y > page_bot || node->y < page_top)
				continue;
		}

		if (node->type == FLOW_WORD || node->type == FLOW_SPACE || node->type == FLOW_SHYPHEN)
		{
			string_walker walker;
			const char *s;
			float x, y;

			if (node->type == FLOW_SPACE && node->breaks_line)
				continue;
			if (node->type == FLOW_SHYPHEN && !node->breaks_line)
				continue;
			if (style->visibility != V_VISIBLE)
				continue;

			color[0] = style->color.r / 255.0f;
			color[1] = style->color.g / 255.0f;
			color[2] = style->color.b / 255.0f;

			if (color[0] != prev_color[0] || color[1] != prev_color[1] || color[2] != prev_color[2])
			{
				if (text)
				{
					fz_fill_text(ctx, dev, text, ctm, fz_device_rgb(ctx), prev_color, 1, fz_default_color_params);
					fz_drop_text(ctx, text);
					text = NULL;
				}
				prev_color[0] = color[0];
				prev_color[1] = color[1];
				prev_color[2] = color[2];
			}

			if (!text)
				text = fz_new_text(ctx);

			if (node->bidi_level & 1)
				x = node->x + node->w;
			else
				x = node->x;
			y = node->y;

			trm.a = node->box->em;
			trm.b = 0;
			trm.c = 0;
			trm.d = -node->box->em;
			trm.e = x;
			trm.f = y - page_top;

			s = get_node_text(ctx, node);
			init_string_walker(ctx, &walker, hb_buf, node->bidi_level & 1, style->font, node->script, node->markup_lang, style->small_caps, s);
			while (walk_string(&walker))
			{
				float node_scale = node->box->em / walker.scale;
				unsigned int i;
				uint32_t k;
				int c, n;

				/* Flatten advance and offset into offset array. */
				int x_advance = 0;
				int y_advance = 0;
				for (i = 0; i < walker.glyph_count; ++i)
				{
					walker.glyph_pos[i].x_offset += x_advance;
					walker.glyph_pos[i].y_offset += y_advance;
					x_advance += walker.glyph_pos[i].x_advance;
					y_advance += walker.glyph_pos[i].y_advance;
				}

				if (node->bidi_level & 1)
					x -= x_advance * node_scale;

				/* Walk characters to find glyph clusters */
				k = 0;
				while (walker.start + k < walker.end)
				{
					n = fz_chartorune(&c, walker.start + k);

					for (i = 0; i < walker.glyph_count; ++i)
					{
						if (walker.glyph_info[i].cluster == k)
						{
							trm.e = x + walker.glyph_pos[i].x_offset * node_scale;
							trm.f = y - walker.glyph_pos[i].y_offset * node_scale - page_top;
							fz_show_glyph(ctx, text, walker.font, trm,
									walker.glyph_info[i].codepoint, c,
									0, node->bidi_level, box->markup_dir, node->markup_lang);
							c = -1; /* for subsequent glyphs in x-to-many mappings */
						}
					}

					/* no glyph found (many-to-many or many-to-one mapping) */
					if (c != -1)
					{
						fz_show_glyph(ctx, text, walker.font, trm,
								-1, c,
								0, node->bidi_level, box->markup_dir, node->markup_lang);
					}

					k += n;
				}

				if ((node->bidi_level & 1) == 0)
					x += x_advance * node_scale;

				y += y_advance * node_scale;
			}
		}
		else if (node->type == FLOW_IMAGE)
		{
			if (text)
			{
				fz_fill_text(ctx, dev, text, ctm, fz_device_rgb(ctx), color, 1, fz_default_color_params);
				fz_drop_text(ctx, text);
				text = NULL;
			}
			if (style->visibility == V_VISIBLE)
			{
				fz_matrix itm = fz_pre_translate(ctm, node->x, node->y - page_top);
				itm = fz_pre_scale(itm, node->w, node->h);
				fz_fill_image(ctx, dev, node->content.image, itm, 1, fz_default_color_params);
			}
		}
	}

	if (text)
	{
		fz_fill_text(ctx, dev, text, ctm, fz_device_rgb(ctx), color, 1, fz_default_color_params);
		fz_drop_text(ctx, text);
		text = NULL;
	}
}