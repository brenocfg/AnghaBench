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

/* Variables and functions */
 int /*<<< orphan*/  cleanupFreeType () ; 
 int /*<<< orphan*/  closeFont () ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  hb_face ; 
 int /*<<< orphan*/  hb_face_get_empty () ; 
 int /*<<< orphan*/  hb_font ; 
 int /*<<< orphan*/  hb_font_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_font_get_empty () ; 
 int /*<<< orphan*/  hb_font_get_face (int /*<<< orphan*/ ) ; 
 int hb_ot_math_has_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initFreeType () ; 
 int /*<<< orphan*/  openFont (char*) ; 

__attribute__((used)) static void
test_has_data (void)
{
  initFreeType();

  openFont("fonts/MathTestFontNone.otf");
  g_assert(!hb_ot_math_has_data (hb_face)); // MATH table not available
  closeFont();

  openFont("fonts/MathTestFontEmpty.otf");
  g_assert(hb_ot_math_has_data (hb_face)); // MATH table available
  closeFont();

  hb_face = hb_face_get_empty ();
  hb_font = hb_font_create (hb_face);
  g_assert(!hb_ot_math_has_data (hb_face)); // MATH table not available

  hb_font = hb_font_get_empty ();
  hb_face = hb_font_get_face (hb_font);
  g_assert(!hb_ot_math_has_data (hb_face)); // MATH table not available

  cleanupFreeType();
}