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
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_5__ {scalar_t__ ft_stretch; } ;
struct TYPE_6__ {float* width_table; int width_count; float width_default; scalar_t__ ft_face; int /*<<< orphan*/  name; TYPE_1__ flags; } ;
typedef  TYPE_2__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {float units_per_EM; } ;
typedef  float FT_Fixed ;
typedef  TYPE_3__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Invalid_Argument ; 
 scalar_t__ FT_Get_Advance (scalar_t__,int,int,float*) ; 
 int FT_LOAD_IGNORE_TRANSFORM ; 
 int FT_LOAD_NO_HINTING ; 
 int FT_LOAD_NO_SCALE ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  ft_error_string (scalar_t__) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pre_scale (int /*<<< orphan*/ ,float,int) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_matrix *
fz_adjust_ft_glyph_width(fz_context *ctx, fz_font *font, int gid, fz_matrix *trm)
{
	/* Fudge the font matrix to stretch the glyph if we've substituted the font. */
	if (font->flags.ft_stretch && font->width_table /* && font->wmode == 0 */)
	{
		FT_Error fterr;
		FT_Fixed adv = 0;
		float subw;
		float realw;

		fz_lock(ctx, FZ_LOCK_FREETYPE);
		fterr = FT_Get_Advance(font->ft_face, gid, FT_LOAD_NO_SCALE | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM, &adv);
		fz_unlock(ctx, FZ_LOCK_FREETYPE);
		if (fterr && fterr != FT_Err_Invalid_Argument)
			fz_warn(ctx, "FT_Get_Advance(%s,%d): %s", font->name, gid, ft_error_string(fterr));

		realw = adv * 1000.0f / ((FT_Face)font->ft_face)->units_per_EM;
		if (gid < font->width_count)
			subw = font->width_table[gid];
		else
			subw = font->width_default;

		/* Sanity check scaling in case of broken metrics. */
		if (realw > 0 && subw > 0)
			*trm = fz_pre_scale(*trm, subw / realw, 1);
	}

	return trm;
}