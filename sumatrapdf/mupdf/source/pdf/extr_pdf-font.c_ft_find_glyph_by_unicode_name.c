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
typedef  int /*<<< orphan*/  FT_Face ;

/* Variables and functions */
 int ft_char_index (int /*<<< orphan*/ ,int) ; 
 int ft_name_index (int /*<<< orphan*/ ,char const*) ; 
 int fz_unicode_from_glyph_name (char const*) ; 
 int fz_unicode_from_glyph_name_strict (char const*) ; 

__attribute__((used)) static int ft_find_glyph_by_unicode_name(FT_Face face, const char *name)
{
	int unicode, glyph;

	/* Prefer exact unicode match if available. */
	unicode = fz_unicode_from_glyph_name_strict(name);
	if (unicode > 0)
	{
		glyph = ft_char_index(face, unicode);
		if (glyph > 0)
			return glyph;
	}

	/* Fall back to font glyph name if we can. */
	glyph = ft_name_index(face, name);
	if (glyph > 0)
		return glyph;

	/* Fuzzy unicode match as last attempt. */
	unicode = fz_unicode_from_glyph_name(name);
	if (unicode > 0)
		return ft_char_index(face, unicode);

	/* Failed. */
	return 0;
}