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
typedef  int /*<<< orphan*/  hb_font_t ;
typedef  int hb_codepoint_t ;
typedef  int /*<<< orphan*/  hb_bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static hb_bool_t
glyph_func (hb_font_t *font, void *font_data,
	    hb_codepoint_t unicode, hb_codepoint_t variant_selector,
	    hb_codepoint_t *glyph,
	    void *user_data)
{
  switch (unicode) {
  case 'T': *glyph = 1; return TRUE;
  case 'e': *glyph = 2; return TRUE;
  case 's': *glyph = 3; return TRUE;
  }
  return FALSE;
}