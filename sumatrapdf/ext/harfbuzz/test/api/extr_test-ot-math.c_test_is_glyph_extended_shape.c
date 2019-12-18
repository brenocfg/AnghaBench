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
typedef  int /*<<< orphan*/  hb_codepoint_t ;

/* Variables and functions */
 int /*<<< orphan*/  cleanupFreeType () ; 
 int /*<<< orphan*/  closeFont () ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  hb_face ; 
 int /*<<< orphan*/  hb_font ; 
 int hb_font_get_glyph_from_name (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int hb_ot_math_is_glyph_extended_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initFreeType () ; 
 int /*<<< orphan*/  openFont (char*) ; 

__attribute__((used)) static void
test_is_glyph_extended_shape (void)
{
  hb_codepoint_t glyph;
  initFreeType();

  openFont("fonts/MathTestFontEmpty.otf");
  g_assert(hb_font_get_glyph_from_name (hb_font, "space", -1, &glyph));
  g_assert(!hb_ot_math_is_glyph_extended_shape (hb_face, glyph)); // MathGlyphInfo not available
  closeFont();

  openFont("fonts/MathTestFontPartial1.otf");
  g_assert(hb_font_get_glyph_from_name (hb_font, "space", -1, &glyph));
  g_assert(!hb_ot_math_is_glyph_extended_shape (hb_face, glyph)); // MathGlyphInfo empty
  closeFont();

  openFont("fonts/MathTestFontFull.otf");
  g_assert(hb_font_get_glyph_from_name (hb_font, "G", -1, &glyph));
  g_assert(!hb_ot_math_is_glyph_extended_shape (hb_face, glyph));
  g_assert(hb_font_get_glyph_from_name (hb_font, "H", -1, &glyph));
  g_assert(hb_ot_math_is_glyph_extended_shape (hb_face, glyph));
  closeFont();

  cleanupFreeType();
}