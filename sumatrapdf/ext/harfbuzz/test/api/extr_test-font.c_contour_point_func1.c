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
typedef  int /*<<< orphan*/  hb_bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static hb_bool_t
contour_point_func1 (hb_font_t *font, void *font_data,
		     hb_codepoint_t glyph, unsigned int point_index,
		     hb_position_t *x, hb_position_t *y,
		     void *user_data)
{
  if (glyph == 1) {
    *x = 2;
    *y = 3;
    return TRUE;
  }
  if (glyph == 2) {
    *x = 4;
    *y = 5;
    return TRUE;
  }

  return FALSE;
}