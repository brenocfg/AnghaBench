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
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  test_get_constant ; 
 int /*<<< orphan*/  test_get_glyph_assembly ; 
 int /*<<< orphan*/  test_get_glyph_assembly_italics_correction ; 
 int /*<<< orphan*/  test_get_glyph_italics_correction ; 
 int /*<<< orphan*/  test_get_glyph_kerning ; 
 int /*<<< orphan*/  test_get_glyph_top_accent_attachment ; 
 int /*<<< orphan*/  test_get_glyph_variants ; 
 int /*<<< orphan*/  test_get_min_connector_overlap ; 
 int /*<<< orphan*/  test_has_data ; 
 int /*<<< orphan*/  test_is_glyph_extended_shape ; 

int
main (int argc, char **argv)
{
  hb_test_init (&argc, &argv);

  hb_test_add (test_has_data);
  hb_test_add (test_get_constant);
  hb_test_add (test_get_glyph_italics_correction);
  hb_test_add (test_get_glyph_top_accent_attachment);
  hb_test_add (test_is_glyph_extended_shape);
  hb_test_add (test_get_glyph_kerning);
  hb_test_add (test_get_glyph_assembly_italics_correction);
  hb_test_add (test_get_min_connector_overlap);
  hb_test_add (test_get_glyph_variants);
  hb_test_add (test_get_glyph_assembly);

  return hb_test_run();
}