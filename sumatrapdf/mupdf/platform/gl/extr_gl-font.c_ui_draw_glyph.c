#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct glyph {float w; float h; float lsb; float top; scalar_t__ t; scalar_t__ s; } ;
typedef  int /*<<< orphan*/  fz_font ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 float floorf (float) ; 
 float fz_advance_glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 float g_cache_h ; 
 float g_cache_w ; 
 int /*<<< orphan*/  glTexCoord2f (float,float) ; 
 int /*<<< orphan*/  glVertex2f (float,float) ; 
 struct glyph* lookup_glyph (int /*<<< orphan*/ *,float,int,float*,float*) ; 

__attribute__((used)) static float ui_draw_glyph(fz_font *font, float size, int gid, float x, float y)
{
	struct glyph *glyph;
	float s0, t0, s1, t1, xc, yc;

	glyph = lookup_glyph(font, size, gid, &x, &y);
	if (!glyph)
		return 0;

	s0 = (float) glyph->s / g_cache_w;
	t0 = (float) glyph->t / g_cache_h;
	s1 = (float) (glyph->s + glyph->w) / g_cache_w;
	t1 = (float) (glyph->t + glyph->h) / g_cache_h;
	xc = floorf(x) + glyph->lsb;
	yc = floorf(y) - glyph->top + glyph->h;

	glTexCoord2f(s0, t0); glVertex2f(xc, yc - glyph->h);
	glTexCoord2f(s1, t0); glVertex2f(xc + glyph->w, yc - glyph->h);
	glTexCoord2f(s1, t1); glVertex2f(xc + glyph->w, yc);
	glTexCoord2f(s0, t1); glVertex2f(xc, yc);

	return fz_advance_glyph(ctx, font, gid, 0) * size;
}