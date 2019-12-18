#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_21__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int char_u ;
struct TYPE_40__ {scalar_t__ data; } ;
struct TYPE_39__ {int width; int /*<<< orphan*/  height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_33__ {scalar_t__ x_offset; int width; } ;
struct TYPE_31__ {scalar_t__ is_cluster_start; } ;
struct TYPE_38__ {TYPE_2__ geometry; TYPE_1__ attr; } ;
struct TYPE_37__ {int* log_clusters; int num_glyphs; TYPE_7__* glyphs; } ;
struct TYPE_30__ {int level; int /*<<< orphan*/  font; int /*<<< orphan*/  shape_engine; } ;
struct TYPE_36__ {int offset; TYPE_13__ analysis; int /*<<< orphan*/  length; } ;
struct TYPE_35__ {TYPE_7__* glyphs; } ;
struct TYPE_34__ {int /*<<< orphan*/ * window; } ;
struct TYPE_32__ {int num_cols; int char_width; int /*<<< orphan*/  text_gc; int /*<<< orphan*/ * text_context; scalar_t__ font_can_bold; int /*<<< orphan*/ * wide_font; int /*<<< orphan*/  ascii_font; TYPE_4__* ascii_glyphs; int /*<<< orphan*/  char_height; int /*<<< orphan*/  border_offset; TYPE_3__* drawarea; } ;
struct TYPE_29__ {scalar_t__ vc_type; } ;
typedef  TYPE_5__ PangoItem ;
typedef  TYPE_6__ PangoGlyphString ;
typedef  TYPE_7__ PangoGlyphInfo ;
typedef  int /*<<< orphan*/  PangoAttrList ;
typedef  TYPE_8__ GdkRectangle ;
typedef  TYPE_9__ GList ;

/* Variables and functions */
 scalar_t__ CONV_NONE ; 
 int DRAW_BOLD ; 
 int DRAW_ITALIC ; 
 int /*<<< orphan*/  FILL_Y (int) ; 
 int /*<<< orphan*/  INSERT_PANGO_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/  PANGO_STYLE_ITALIC ; 
 int /*<<< orphan*/  PANGO_WEIGHT_BOLD ; 
 int* alloc (int) ; 
 int /*<<< orphan*/  apply_wide_font_attr (int*,int,int /*<<< orphan*/ *) ; 
 int count_cluster_cells (int*,TYPE_5__*,TYPE_6__*,int,int*,int*) ; 
 int /*<<< orphan*/  default_shape_engine ; 
 int /*<<< orphan*/  draw_glyph_string (int,int,int,int,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  draw_under (int,int,int,int) ; 
 TYPE_9__* g_list_delete_link (TYPE_9__*,TYPE_9__*) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdk_gc_set_clip_origin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_gc_set_clip_rectangle (int /*<<< orphan*/ ,TYPE_8__*) ; 
 TYPE_21__ gui ; 
 int mb_ptr2cells (int*) ; 
 int /*<<< orphan*/  mb_ptr2len (int*) ; 
 int /*<<< orphan*/  mch_memmove (int*,int*,int) ; 
 TYPE_10__ output_conv ; 
 int /*<<< orphan*/ * pango_attr_list_new () ; 
 int /*<<< orphan*/  pango_attr_list_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_attr_style_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_attr_weight_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_glyph_string_free (TYPE_6__*) ; 
 TYPE_6__* pango_glyph_string_new () ; 
 int /*<<< orphan*/  pango_glyph_string_set_size (TYPE_6__*,int) ; 
 int /*<<< orphan*/  pango_item_free (TYPE_5__*) ; 
 TYPE_9__* pango_itemize (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_shape (char const*,int /*<<< orphan*/ ,TYPE_13__*,TYPE_6__*) ; 
 int /*<<< orphan*/  setup_zero_width_cluster (TYPE_5__*,TYPE_7__*,int,int,int) ; 
 int* string_convert (TYPE_10__*,int*,int*) ; 
 int stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*) ; 
 int utf_ptr2cells (int*) ; 
 int utf_ptr2len (int*) ; 
 int /*<<< orphan*/  utf_valid_string (int*,int*) ; 
 int /*<<< orphan*/  vim_free (int*) ; 

int
gui_gtk2_draw_string(int row, int col, char_u *s, int len, int flags)
{
    GdkRectangle	area;		    /* area for clip mask	  */
    PangoGlyphString	*glyphs;	    /* glyphs of current item	  */
    int			column_offset = 0;  /* column offset in cells	  */
    int			i;
    char_u		*conv_buf = NULL;   /* result of UTF-8 conversion */
    char_u		*new_conv_buf;
    int			convlen;
    char_u		*sp, *bp;
    int			plen;

    if (gui.text_context == NULL || gui.drawarea->window == NULL)
	return len;

    if (output_conv.vc_type != CONV_NONE)
    {
	/*
	 * Convert characters from 'encoding' to 'termencoding', which is set
	 * to UTF-8 by gui_mch_init().	did_set_string_option() in option.c
	 * prohibits changing this to something else than UTF-8 if the GUI is
	 * in use.
	 */
	convlen = len;
	conv_buf = string_convert(&output_conv, s, &convlen);
	g_return_val_if_fail(conv_buf != NULL, len);

	/* Correct for differences in char width: some chars are
	 * double-wide in 'encoding' but single-wide in utf-8.  Add a space to
	 * compensate for that. */
	for (sp = s, bp = conv_buf; sp < s + len && bp < conv_buf + convlen; )
	{
	    plen = utf_ptr2len(bp);
	    if ((*mb_ptr2cells)(sp) == 2 && utf_ptr2cells(bp) == 1)
	    {
		new_conv_buf = alloc(convlen + 2);
		if (new_conv_buf == NULL)
		    return len;
		plen += bp - conv_buf;
		mch_memmove(new_conv_buf, conv_buf, plen);
		new_conv_buf[plen] = ' ';
		mch_memmove(new_conv_buf + plen + 1, conv_buf + plen,
							  convlen - plen + 1);
		vim_free(conv_buf);
		conv_buf = new_conv_buf;
		++convlen;
		bp = conv_buf + plen;
		plen = 1;
	    }
	    sp += (*mb_ptr2len)(sp);
	    bp += plen;
	}
	s = conv_buf;
	len = convlen;
    }

    /*
     * Restrict all drawing to the current screen line in order to prevent
     * fuzzy font lookups from messing up the screen.
     */
    area.x = gui.border_offset;
    area.y = FILL_Y(row);
    area.width	= gui.num_cols * gui.char_width;
    area.height = gui.char_height;

    gdk_gc_set_clip_origin(gui.text_gc, 0, 0);
    gdk_gc_set_clip_rectangle(gui.text_gc, &area);

    glyphs = pango_glyph_string_new();

    /*
     * Optimization hack:  If possible, skip the itemize and shaping process
     * for pure ASCII strings.	This optimization is particularly effective
     * because Vim draws space characters to clear parts of the screen.
     */
    if (!(flags & DRAW_ITALIC)
	    && !((flags & DRAW_BOLD) && gui.font_can_bold)
	    && gui.ascii_glyphs != NULL)
    {
	char_u *p;

	for (p = s; p < s + len; ++p)
	    if (*p & 0x80)
		goto not_ascii;

	pango_glyph_string_set_size(glyphs, len);

	for (i = 0; i < len; ++i)
	{
	    glyphs->glyphs[i] = gui.ascii_glyphs->glyphs[s[i]];
	    glyphs->log_clusters[i] = i;
	}

	draw_glyph_string(row, col, len, flags, gui.ascii_font, glyphs);

	column_offset = len;
    }
    else
not_ascii:
    {
	PangoAttrList	*attr_list;
	GList		*item_list;
	int		cluster_width;
	int		last_glyph_rbearing;
	int		cells = 0;  /* cells occupied by current cluster */

	/* Safety check: pango crashes when invoked with invalid utf-8
	 * characters. */
	if (!utf_valid_string(s, s + len))
	{
	    column_offset = len;
	    goto skipitall;
	}

	/* original width of the current cluster */
	cluster_width = PANGO_SCALE * gui.char_width;

	/* right bearing of the last non-composing glyph */
	last_glyph_rbearing = PANGO_SCALE * gui.char_width;

	attr_list = pango_attr_list_new();

	/* If 'guifontwide' is set then use that for double-width characters.
	 * Otherwise just go with 'guifont' and let Pango do its thing. */
	if (gui.wide_font != NULL)
	    apply_wide_font_attr(s, len, attr_list);

	if ((flags & DRAW_BOLD) && gui.font_can_bold)
	    INSERT_PANGO_ATTR(pango_attr_weight_new(PANGO_WEIGHT_BOLD),
			      attr_list, 0, len);
	if (flags & DRAW_ITALIC)
	    INSERT_PANGO_ATTR(pango_attr_style_new(PANGO_STYLE_ITALIC),
			      attr_list, 0, len);
	/*
	 * Break the text into segments with consistent directional level
	 * and shaping engine.	Pure Latin text needs only a single segment,
	 * so there's no need to worry about the loop's efficiency.  Better
	 * try to optimize elsewhere, e.g. reducing exposes and stuff :)
	 */
	item_list = pango_itemize(gui.text_context,
				  (const char *)s, 0, len, attr_list, NULL);

	while (item_list != NULL)
	{
	    PangoItem	*item;
	    int		item_cells = 0; /* item length in cells */

	    item = (PangoItem *)item_list->data;
	    item_list = g_list_delete_link(item_list, item_list);
	    /*
	     * Increment the bidirectional embedding level by 1 if it is not
	     * even.  An odd number means the output will be RTL, but we don't
	     * want that since Vim handles right-to-left text on its own.  It
	     * would probably be sufficient to just set level = 0, but you can
	     * never know :)
	     *
	     * Unfortunately we can't take advantage of Pango's ability to
	     * render both LTR and RTL at the same time.  In order to support
	     * that, Vim's main screen engine would have to make use of Pango
	     * functionality.
	     */
	    item->analysis.level = (item->analysis.level + 1) & (~1U);

	    /* HACK: Overrule the shape engine, we don't want shaping to be
	     * done, because drawing the cursor would change the display. */
	    item->analysis.shape_engine = default_shape_engine;

	    pango_shape((const char *)s + item->offset, item->length,
			&item->analysis, glyphs);
	    /*
	     * Fixed-width hack: iterate over the array and assign a fixed
	     * width to each glyph, thus overriding the choice made by the
	     * shaping engine.	We use utf_char2cells() to determine the
	     * number of cells needed.
	     *
	     * Also perform all kind of dark magic to get composing
	     * characters right (and pretty too of course).
	     */
	    for (i = 0; i < glyphs->num_glyphs; ++i)
	    {
		PangoGlyphInfo *glyph;

		glyph = &glyphs->glyphs[i];

		if (glyph->attr.is_cluster_start)
		{
		    int cellcount;

		    cellcount = count_cluster_cells(
			s, item, glyphs, i, &cluster_width,
			(item_list != NULL) ? &last_glyph_rbearing : NULL);

		    if (cellcount > 0)
		    {
			int width;

			width = cellcount * gui.char_width * PANGO_SCALE;
			glyph->geometry.x_offset +=
					    MAX(0, width - cluster_width) / 2;
			glyph->geometry.width = width;
		    }
		    else
		    {
			/* If there are only combining characters in the
			 * cluster, we cannot just change the width of the
			 * previous glyph since there is none.	Therefore
			 * some guesswork is needed. */
			setup_zero_width_cluster(item, glyph, cells,
						 cluster_width,
						 last_glyph_rbearing);
		    }

		    item_cells += cellcount;
		    cells = cellcount;
		}
		else if (i > 0)
		{
		    int width;

		    /* There is a previous glyph, so we deal with combining
		     * characters the canonical way.
		     * In some circumstances Pango uses a positive x_offset,
		     * then use the width of the previous glyph for this one
		     * and set the previous width to zero.
		     * Otherwise we get a negative x_offset, Pango has already
		     * positioned the combining char, keep the widths as they
		     * are.
		     * For both adjust the x_offset to position the glyph in
		     * the middle. */
		    if (glyph->geometry.x_offset >= 0)
		    {
			glyphs->glyphs[i].geometry.width =
					 glyphs->glyphs[i - 1].geometry.width;
			glyphs->glyphs[i - 1].geometry.width = 0;
		    }
		    width = cells * gui.char_width * PANGO_SCALE;
		    glyph->geometry.x_offset +=
					    MAX(0, width - cluster_width) / 2;
		}
		else /* i == 0 "cannot happen" */
		{
		    glyph->geometry.width = 0;
		}
	    }

	    /*** Aaaaand action! ***/
	    draw_glyph_string(row, col + column_offset, item_cells,
			      flags, item->analysis.font, glyphs);

	    pango_item_free(item);

	    column_offset += item_cells;
	}

	pango_attr_list_unref(attr_list);
    }

skipitall:
    /* Draw underline and undercurl. */
    draw_under(flags, row, col, column_offset);

    pango_glyph_string_free(glyphs);
    vim_free(conv_buf);

    gdk_gc_set_clip_rectangle(gui.text_gc, NULL);

    return column_offset;
}