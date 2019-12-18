#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ft_stretch; } ;
struct TYPE_6__ {float* width_table; int width_count; float width_default; scalar_t__ ft_face; int /*<<< orphan*/  name; TYPE_1__ flags; } ;
typedef  TYPE_2__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {float units_per_EM; } ;
typedef  scalar_t__ FT_Fixed ;
typedef  TYPE_3__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Invalid_Argument ; 
 scalar_t__ FT_Get_Advance (scalar_t__,int,int,scalar_t__*) ; 
 int FT_LOAD_IGNORE_TRANSFORM ; 
 int FT_LOAD_NO_HINTING ; 
 int FT_LOAD_NO_SCALE ; 
 int FT_LOAD_VERTICAL_LAYOUT ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  ft_error_string (scalar_t__) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float
fz_advance_ft_glyph(fz_context *ctx, fz_font *font, int gid, int wmode)
{
	FT_Error fterr;
	FT_Fixed adv = 0;
	int mask;

	/* PDF and substitute font widths. */
	if (font->flags.ft_stretch)
	{
		if (font->width_table)
		{
			if (gid < font->width_count)
				return font->width_table[gid] / 1000.0f;
			return font->width_default / 1000.0f;
		}
	}

	mask = FT_LOAD_NO_SCALE | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM;
	if (wmode)
		mask |= FT_LOAD_VERTICAL_LAYOUT;
	fz_lock(ctx, FZ_LOCK_FREETYPE);
	fterr = FT_Get_Advance(font->ft_face, gid, mask, &adv);
	fz_unlock(ctx, FZ_LOCK_FREETYPE);
	if (fterr && fterr != FT_Err_Invalid_Argument)
	{
		fz_warn(ctx, "FT_Get_Advance(%s,%d): %s", font->name, gid, ft_error_string(fterr));
		if (font->width_table)
		{
			if (gid < font->width_count)
				return font->width_table[gid] / 1000.0f;
			return font->width_default / 1000.0f;
		}
	}
	return (float) adv / ((FT_Face)font->ft_face)->units_per_EM;
}