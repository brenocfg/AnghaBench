#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
struct genstate {int at_bol; int emit_white; int /*<<< orphan*/  pool; int /*<<< orphan*/  styles; scalar_t__ is_fb2; int /*<<< orphan*/  set; int /*<<< orphan*/  images; int /*<<< orphan*/  base_uri; int /*<<< orphan*/  zip; int /*<<< orphan*/  css; } ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_image ;
struct TYPE_45__ {scalar_t__ type; char heading; int list_item; TYPE_5__* style; void* href; void* id; struct TYPE_45__* up; } ;
typedef  TYPE_4__ fz_html_box ;
struct TYPE_44__ {int value; int /*<<< orphan*/  unit; } ;
struct TYPE_43__ {int value; void* unit; } ;
struct TYPE_42__ {int value; void* unit; } ;
struct TYPE_46__ {int white_space; TYPE_3__ font_size; TYPE_2__ height; TYPE_1__ width; } ;
typedef  TYPE_5__ fz_css_style ;
struct TYPE_47__ {scalar_t__ count; struct TYPE_47__* up; } ;
typedef  TYPE_6__ fz_css_match ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  BOX_BLOCK ; 
 scalar_t__ BOX_FLOW ; 
 scalar_t__ BOX_INLINE ; 
 int DEFAULT_DIR ; 
 int DIS_BLOCK ; 
 int DIS_INLINE ; 
 int DIS_INLINE_BLOCK ; 
 int DIS_LIST_ITEM ; 
 int DIS_NONE ; 
 int DIS_TABLE ; 
 int DIS_TABLE_CELL ; 
 int DIS_TABLE_ROW ; 
 int FZ_BIDI_LTR ; 
 int FZ_BIDI_NEUTRAL ; 
 int FZ_BIDI_RTL ; 
 void* N_LENGTH ; 
 void* N_PERCENT ; 
 int /*<<< orphan*/  N_SCALE ; 
 int WS_COLLAPSE ; 
 int /*<<< orphan*/  add_flow_break (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fz_apply_css_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*) ; 
 int fz_atoi (char const*) ; 
 void* fz_css_enlist (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_default_css_style (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int fz_get_css_match_display (TYPE_6__*) ; 
 int /*<<< orphan*/  fz_keep_image (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_match_css (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char fz_mini (int,int) ; 
 void* fz_pool_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int fz_text_language_from_string (char const*) ; 
 int /*<<< orphan*/ * fz_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 char* fz_xml_tag (int /*<<< orphan*/ *) ; 
 char* fz_xml_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_anchor (int /*<<< orphan*/ *,TYPE_4__*,struct genstate*) ; 
 int /*<<< orphan*/  generate_image (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,struct genstate*) ; 
 int /*<<< orphan*/  generate_text (int /*<<< orphan*/ *,TYPE_4__*,char const*,int,struct genstate*) ; 
 TYPE_4__* insert_block_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  insert_box (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* insert_break_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  insert_inline_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*,int,struct genstate*) ; 
 TYPE_4__* insert_table_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* insert_table_cell_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* insert_table_row_box (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ is_all_white (char const*) ; 
 int /*<<< orphan*/  load_html_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  load_svg_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* new_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* new_short_box (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static fz_html_box *
generate_boxes(fz_context *ctx,
	fz_xml *node,
	fz_html_box *top,
	fz_css_match *up_match,
	int list_counter,
	int section_depth,
	int markup_dir,
	int markup_lang,
	struct genstate *g)
{
	fz_css_match match;
	fz_html_box *box, *last_top;
	const char *tag;
	int display;
	fz_css_style style;

	while (node)
	{
		match.up = up_match;
		match.count = 0;

		tag = fz_xml_tag(node);
		if (tag)
		{
			fz_match_css(ctx, &match, g->css, node);

			display = fz_get_css_match_display(&match);

			if (tag[0]=='b' && tag[1]=='r' && tag[2]==0)
			{
				if (top->type == BOX_INLINE)
				{
					fz_html_box *flow = top;
					while (flow->type != BOX_FLOW)
						flow = flow->up;
					add_flow_break(ctx, g->pool, flow, top);
				}
				else
				{
					box = new_short_box(ctx, g->pool, markup_dir);
					fz_apply_css_style(ctx, g->set, &style, &match);
					box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
					top = insert_break_box(ctx, box, top);
				}
				g->at_bol = 1;
			}

			else if (tag[0]=='i' && tag[1]=='m' && tag[2]=='g' && tag[3]==0)
			{
				const char *src = fz_xml_att(node, "src");
				if (src)
				{
					int w, h;
					const char *w_att = fz_xml_att(node, "width");
					const char *h_att = fz_xml_att(node, "height");
					box = new_short_box(ctx, g->pool, markup_dir);
					fz_apply_css_style(ctx, g->set, &style, &match);
					if (w_att && (w = fz_atoi(w_att)) > 0)
					{
						style.width.value = w;
						style.width.unit = strchr(w_att, '%') ? N_PERCENT : N_LENGTH;
					}
					if (h_att && (h = fz_atoi(h_att)) > 0)
					{
						style.height.value = h;
						style.height.unit = strchr(h_att, '%') ? N_PERCENT : N_LENGTH;
					}
					box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
					insert_inline_box(ctx, box, top, markup_dir, g);
					generate_image(ctx, box, load_html_image(ctx, g->zip, g->base_uri, src), g);
				}
			}

			else if (tag[0]=='s' && tag[1]=='v' && tag[2]=='g' && tag[3]==0)
			{
				box = new_short_box(ctx, g->pool, markup_dir);
				fz_apply_css_style(ctx, g->set, &style, &match);
				box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
				insert_inline_box(ctx, box, top, markup_dir, g);
				generate_image(ctx, box, load_svg_image(ctx, g->zip, g->base_uri, node), g);
			}

			else if (g->is_fb2 && tag[0]=='i' && tag[1]=='m' && tag[2]=='a' && tag[3]=='g' && tag[4]=='e' && tag[5]==0)
			{
				const char *src = fz_xml_att(node, "l:href");
				if (!src)
					src = fz_xml_att(node, "xlink:href");
				if (src && src[0] == '#')
				{
					fz_image *img = fz_tree_lookup(ctx, g->images, src+1);
					if (display == DIS_BLOCK)
					{
						fz_html_box *imgbox;
						box = new_box(ctx, g->pool, markup_dir);
						fz_default_css_style(ctx, &style);
						fz_apply_css_style(ctx, g->set, &style, &match);
						box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
						top = insert_block_box(ctx, box, top);
						imgbox = new_short_box(ctx, g->pool, markup_dir);
						fz_apply_css_style(ctx, g->set, &style, &match);
						imgbox->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
						insert_inline_box(ctx, imgbox, box, markup_dir, g);
						generate_image(ctx, imgbox, fz_keep_image(ctx, img), g);
					}
					else if (display == DIS_INLINE)
					{
						box = new_short_box(ctx, g->pool, markup_dir);
						fz_apply_css_style(ctx, g->set, &style, &match);
						box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
						insert_inline_box(ctx, box, top, markup_dir, g);
						generate_image(ctx, box, fz_keep_image(ctx, img), g);
					}
				}
			}

			else if (display != DIS_NONE)
			{
				const char *dir, *lang, *id, *href;
				int child_dir = markup_dir;
				int child_lang = markup_lang;

				dir = fz_xml_att(node, "dir");
				if (dir)
				{
					if (!strcmp(dir, "auto"))
						child_dir = FZ_BIDI_NEUTRAL;
					else if (!strcmp(dir, "rtl"))
						child_dir = FZ_BIDI_RTL;
					else if (!strcmp(dir, "ltr"))
						child_dir = FZ_BIDI_LTR;
					else
						child_dir = DEFAULT_DIR;
				}

				lang = fz_xml_att(node, "lang");
				if (lang)
					child_lang = fz_text_language_from_string(lang);

				if (display == DIS_INLINE)
					box = new_short_box(ctx, g->pool, child_dir);
				else
					box = new_box(ctx, g->pool, child_dir);
				fz_default_css_style(ctx, &style);
				fz_apply_css_style(ctx, g->set, &style, &match);
				box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);

				id = fz_xml_att(node, "id");
				if (id)
					box->id = fz_pool_strdup(ctx, g->pool, id);

				if (display == DIS_BLOCK || display == DIS_INLINE_BLOCK)
				{
					top = insert_block_box(ctx, box, top);
					if (g->is_fb2)
					{
						if (!strcmp(tag, "title") || !strcmp(tag, "subtitle"))
							box->heading = fz_mini(section_depth, 6);
					}
					else
					{
						if (tag[0]=='h' && tag[1]>='1' && tag[1]<='6' && tag[2]==0)
							box->heading = tag[1] - '0';
					}
				}
				else if (display == DIS_LIST_ITEM)
				{
					top = insert_block_box(ctx, box, top);
					box->list_item = ++list_counter;
				}
				else if (display == DIS_INLINE)
				{
					insert_inline_box(ctx, box, top, child_dir, g);
					if (id)
						generate_anchor(ctx, box, g);
					if (tag[0]=='a' && tag[1]==0)
					{
						if (g->is_fb2)
						{
							href = fz_xml_att(node, "l:href");
							if (!href)
								href = fz_xml_att(node, "xlink:href");
						}
						else
							href = fz_xml_att(node, g->is_fb2 ? "l:href" : "href");
						if (href)
							box->href = fz_pool_strdup(ctx, g->pool, href);
					}
				}
				else if (display == DIS_TABLE)
				{
					top = insert_table_box(ctx, box, top);
				}
				else if (display == DIS_TABLE_ROW)
				{
					top = insert_table_row_box(ctx, box, top);
				}
				else if (display == DIS_TABLE_CELL)
				{
					top = insert_table_cell_box(ctx, box, top);
				}
				else
				{
					fz_warn(ctx, "unknown box display type");
					insert_box(ctx, box, BOX_BLOCK, top);
				}

				if (fz_xml_down(node))
				{
					int child_counter = list_counter;
					int child_section = section_depth;
					if (!strcmp(tag, "ul") || !strcmp(tag, "ol"))
						child_counter = 0;
					if (!strcmp(tag, "section"))
						++child_section;
					last_top = generate_boxes(ctx,
						fz_xml_down(node),
						box,
						&match,
						child_counter,
						child_section,
						child_dir,
						child_lang,
						g);
					if (last_top != box)
						top = last_top;
				}
			}
		}
		else
		{
			const char *text = fz_xml_text(node);
			int collapse = top->style->white_space & WS_COLLAPSE;
			if (collapse && is_all_white(text))
			{
				g->emit_white = 1;
			}
			else
			{
				if (top->type != BOX_INLINE)
				{
					/* Create anonymous inline box, with the same style as the top block box. */
					fz_css_style style;
					box = new_short_box(ctx, g->pool, markup_dir);
					fz_default_css_style(ctx, &style);
					box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
					insert_inline_box(ctx, box, top, markup_dir, g);
					style = *top->style;
					/* Make sure not to recursively multiply font sizes. */
					style.font_size.value = 1;
					style.font_size.unit = N_SCALE;
					box->style = fz_css_enlist(ctx, &style, &g->styles, g->pool);
					generate_text(ctx, box, text, markup_lang, g);
				}
				else
				{
					generate_text(ctx, top, text, markup_lang, g);
				}
			}
		}

		node = fz_xml_next(node);
	}

	return top;
}