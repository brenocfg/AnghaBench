#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ft_face; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FT_Get_Name_Index (scalar_t__,char*) ; 
 int UCDN_GENERAL_CATEGORY_LL ; 
 int UCDN_GENERAL_CATEGORY_LT ; 
 int fz_encode_character (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 char* fz_glyph_name_from_unicode_sc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int ucdn_get_general_category (int) ; 

int
fz_encode_character_sc(fz_context *ctx, fz_font *font, int unicode)
{
	if (font->ft_face)
	{
		int cat = ucdn_get_general_category(unicode);
		if (cat == UCDN_GENERAL_CATEGORY_LL || cat == UCDN_GENERAL_CATEGORY_LT)
		{
			int glyph;
			const char *name;
			char buf[20];

			name = fz_glyph_name_from_unicode_sc(unicode);
			if (name)
			{
				glyph = FT_Get_Name_Index(font->ft_face, (char*)name);
				if (glyph > 0)
					return glyph;
			}

			sprintf(buf, "uni%04X.sc", unicode);
			glyph = FT_Get_Name_Index(font->ft_face, buf);
			if (glyph > 0)
				return glyph;
		}
	}
	return fz_encode_character(ctx, font, unicode);
}