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
typedef  int /*<<< orphan*/  hb_position_t ;
typedef  int /*<<< orphan*/  hb_font_t ;
typedef  int /*<<< orphan*/  hb_codepoint_t ;
typedef  scalar_t__ hb_bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_DIRECTION_LTR ; 
 int /*<<< orphan*/  HB_DIRECTION_TTB ; 
 int /*<<< orphan*/  hb_ot_math_get_glyph_assembly (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_position_t
get_glyph_assembly_italics_correction (hb_font_t *font,
				       hb_codepoint_t glyph,
				       hb_bool_t horizontal)
{
  hb_position_t corr;
  hb_ot_math_get_glyph_assembly (font, glyph,
				 horizontal ? HB_DIRECTION_LTR : HB_DIRECTION_TTB,
				 0, NULL, NULL,
				 &corr);
  return corr;
}