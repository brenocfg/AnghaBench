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
typedef  int hb_position_t ;
typedef  int /*<<< orphan*/  hb_font_t ;
typedef  int hb_codepoint_t ;

/* Variables and functions */

__attribute__((used)) static hb_position_t
glyph_h_kerning_func (hb_font_t *font, void *font_data,
		      hb_codepoint_t left, hb_codepoint_t right,
		      void *user_data)
{
  if (left == 1 && right == 2)
    return -2;

  return 0;
}