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
struct TYPE_3__ {int /*<<< orphan*/  name; scalar_t__ ft_face; } ;
typedef  TYPE_1__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  scalar_t__ FT_Face ;

/* Variables and functions */
 int FT_Get_Glyph_Name (scalar_t__,int,char*,int) ; 
 scalar_t__ FT_HAS_GLYPH_NAMES (scalar_t__) ; 
 int /*<<< orphan*/  ft_error_string (int) ; 
 int /*<<< orphan*/  fz_snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
fz_get_glyph_name(fz_context *ctx, fz_font *font, int glyph, char *buf, int size)
{
	FT_Face face = font->ft_face;
	if (face)
	{
		if (FT_HAS_GLYPH_NAMES(face))
		{
			int fterr = FT_Get_Glyph_Name(face, glyph, buf, size);
			if (fterr)
				fz_warn(ctx, "FT_Get_Glyph_Name(%s,%d): %s", font->name, glyph, ft_error_string(fterr));
		}
		else
			fz_snprintf(buf, size, "%d", glyph);
	}
	else
	{
		fz_snprintf(buf, size, "%d", glyph);
	}
}