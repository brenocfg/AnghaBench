#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ft_face; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int ft_char_index (scalar_t__,int /*<<< orphan*/ ) ; 
 int ft_name_index (scalar_t__,char const*) ; 
 int /*<<< orphan*/  fz_unicode_from_glyph_name (char const*) ; 

int
fz_encode_character_by_glyph_name(fz_context *ctx, fz_font *font, const char *glyphname)
{
	int glyph = 0;
	if (font->ft_face)
	{
		glyph = ft_name_index(font->ft_face, glyphname);
		if (glyph == 0)
			glyph = ft_char_index(font->ft_face, fz_unicode_from_glyph_name(glyphname));
	}
	// TODO: type3 fonts (not needed for now)
	return glyph;
}