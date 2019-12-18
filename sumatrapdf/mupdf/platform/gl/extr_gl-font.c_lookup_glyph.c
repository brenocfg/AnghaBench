#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct key {float size; int gid; unsigned char subx; unsigned char suby; int /*<<< orphan*/ * font; } ;
struct glyph {int w; int h; scalar_t__ t; scalar_t__ s; int /*<<< orphan*/  top; int /*<<< orphan*/  lsb; } ;
struct TYPE_11__ {int w; int h; int /*<<< orphan*/  samples; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_pixmap ;
struct TYPE_12__ {float e; float f; } ;
typedef  TYPE_2__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
struct TYPE_13__ {scalar_t__ font; } ;
struct TYPE_14__ {struct glyph glyph; TYPE_3__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ALPHA ; 
 int /*<<< orphan*/  GL_QUADS ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNPACK_ROW_LENGTH ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int MAXGLYPHS ; 
 scalar_t__ PADDING ; 
 int /*<<< orphan*/  clear_font_cache () ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* fz_render_glyph_pixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ fz_scale (float,float) ; 
 int /*<<< orphan*/  fz_subpixel_adjust (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,unsigned char*,unsigned char*) ; 
 scalar_t__ g_cache_h ; 
 scalar_t__ g_cache_row_h ; 
 scalar_t__ g_cache_row_x ; 
 scalar_t__ g_cache_row_y ; 
 scalar_t__ g_cache_w ; 
 TYPE_4__* g_table ; 
 int g_table_load ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTexSubImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int lookup_table (struct key*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct key*,int) ; 
 int /*<<< orphan*/  memset (struct key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static struct glyph *lookup_glyph(fz_font *font, float size, int gid, float *xp, float *yp)
{
	fz_matrix trm, subpix_trm;
	unsigned char subx, suby;
	fz_pixmap *pixmap;
	struct key key;
	unsigned int pos;
	int w, h;

	/* match fitz's glyph cache quantization */
	trm = fz_scale(size, -size);
	trm.e = *xp;
	trm.f = *yp;
	fz_subpixel_adjust(ctx, &trm, &subpix_trm, &subx, &suby);
	*xp = trm.e;
	*yp = trm.f;

	/*
	 * Look it up in the table
	 */

	memset(&key, 0, sizeof key);
	key.font = font;
	key.size = size;
	key.gid = gid;
	key.subx = subx;
	key.suby = suby;

	pos = lookup_table(&key);
	if (g_table[pos].key.font)
		return &g_table[pos].glyph;

	/*
	 * Render the bitmap
	 */

	glEnd();

	pixmap = fz_render_glyph_pixmap(ctx, font, gid, &subpix_trm, NULL, 8);
	w = pixmap->w;
	h = pixmap->h;

	/*
	 * Find an empty slot in the texture
	 */

	if (g_table_load == (MAXGLYPHS * 3) / 4)
	{
		puts("font cache table full, clearing cache");
		clear_font_cache();
		pos = lookup_table(&key);
	}

	if (h + PADDING > g_cache_h || w + PADDING > g_cache_w)
		return NULL;

	if (g_cache_row_x + w + PADDING > g_cache_w)
	{
		g_cache_row_y += g_cache_row_h + PADDING;
		g_cache_row_x = PADDING;
		g_cache_row_h = 0;
	}
	if (g_cache_row_y + h + PADDING > g_cache_h)
	{
		puts("font cache texture full, clearing cache");
		clear_font_cache();
		pos = lookup_table(&key);
	}

	/*
	 * Copy bitmap into texture
	 */

	memcpy(&g_table[pos].key, &key, sizeof(struct key));
	g_table[pos].glyph.w = pixmap->w;
	g_table[pos].glyph.h = pixmap->h;
	g_table[pos].glyph.lsb = pixmap->x;
	g_table[pos].glyph.top = -pixmap->y;
	g_table[pos].glyph.s = g_cache_row_x;
	g_table[pos].glyph.t = g_cache_row_y;
	g_table_load ++;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, pixmap->w);
	glTexSubImage2D(GL_TEXTURE_2D, 0, g_cache_row_x, g_cache_row_y, w, h,
			GL_ALPHA, GL_UNSIGNED_BYTE, pixmap->samples);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	fz_drop_pixmap(ctx, pixmap);

	glBegin(GL_QUADS);

	g_cache_row_x += w + PADDING;
	if (g_cache_row_h < h + PADDING)
		g_cache_row_h = h + PADDING;

	return &g_table[pos].glyph;
}