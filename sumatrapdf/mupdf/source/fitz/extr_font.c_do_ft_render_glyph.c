#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int a; int b; int c; int d; int e; int f; } ;
typedef  TYPE_2__ fz_matrix ;
struct TYPE_22__ {scalar_t__ fake_bold; scalar_t__ fake_italic; } ;
struct TYPE_24__ {int /*<<< orphan*/  name; TYPE_1__ flags; TYPE_7__* ft_face; } ;
typedef  TYPE_3__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_28__ {TYPE_6__* glyph; } ;
struct TYPE_27__ {int /*<<< orphan*/  outline; } ;
struct TYPE_26__ {int xx; int yx; int xy; int yy; } ;
struct TYPE_25__ {int x; int y; } ;
typedef  TYPE_4__ FT_Vector ;
typedef  TYPE_5__ FT_Matrix ;
typedef  TYPE_6__* FT_GlyphSlot ;
typedef  TYPE_7__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 int FT_LOAD_NO_BITMAP ; 
 int FT_LOAD_NO_HINTING ; 
 int FT_LOAD_TARGET_MONO ; 
 scalar_t__ FT_Load_Glyph (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  FT_Outline_Embolden (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  FT_Outline_Translate (int /*<<< orphan*/ *,float,float) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_MONO ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 scalar_t__ FT_Render_Glyph (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Set_Char_Size (TYPE_7__*,int,int,int,int) ; 
 int /*<<< orphan*/  FT_Set_Transform (TYPE_7__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  SHEAR ; 
 int /*<<< orphan*/  ft_error_string (scalar_t__) ; 
 int /*<<< orphan*/  fz_adjust_ft_glyph_width (int /*<<< orphan*/ *,TYPE_3__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float fz_matrix_expansion (TYPE_2__) ; 
 TYPE_2__ fz_pre_shear (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static FT_GlyphSlot
do_ft_render_glyph(fz_context *ctx, fz_font *font, int gid, fz_matrix trm, int aa)
{
	FT_Face face = font->ft_face;
	FT_Matrix m;
	FT_Vector v;
	FT_Error fterr;

	float strength = fz_matrix_expansion(trm) * 0.02f;

	fz_adjust_ft_glyph_width(ctx, font, gid, &trm);

	if (font->flags.fake_italic)
		trm = fz_pre_shear(trm, SHEAR, 0);

	fz_lock(ctx, FZ_LOCK_FREETYPE);

	if (aa == 0)
	{
		/* enable grid fitting for non-antialiased rendering */
		float scale = fz_matrix_expansion(trm);
		m.xx = trm.a * 65536 / scale;
		m.yx = trm.b * 65536 / scale;
		m.xy = trm.c * 65536 / scale;
		m.yy = trm.d * 65536 / scale;
		v.x = 0;
		v.y = 0;

		fterr = FT_Set_Char_Size(face, 64 * scale, 64 * scale, 72, 72);
		if (fterr)
			fz_warn(ctx, "FT_Set_Char_Size(%s,%d,72): %s", font->name, (int)(64*scale), ft_error_string(fterr));
		FT_Set_Transform(face, &m, &v);
		fterr = FT_Load_Glyph(face, gid, FT_LOAD_NO_BITMAP | FT_LOAD_TARGET_MONO);
		if (fterr)
		{
			fz_warn(ctx, "FT_Load_Glyph(%s,%d,FT_LOAD_TARGET_MONO): %s", font->name, gid, ft_error_string(fterr));
			goto retry_unhinted;
		}
	}
	else
	{
retry_unhinted:
		/*
		 * Freetype mutilates complex glyphs if they are loaded with
		 * FT_Set_Char_Size 1.0. It rounds the coordinates before applying
		 * transformation. To get more precision in freetype, we shift part of
		 * the scale in the matrix into FT_Set_Char_Size instead.
		 */

		/* Check for overflow; FreeType matrices use 16.16 fixed-point numbers */
		if (trm.a < -512 || trm.a > 512) return NULL;
		if (trm.b < -512 || trm.b > 512) return NULL;
		if (trm.c < -512 || trm.c > 512) return NULL;
		if (trm.d < -512 || trm.d > 512) return NULL;

		m.xx = trm.a * 64; /* should be 65536 */
		m.yx = trm.b * 64;
		m.xy = trm.c * 64;
		m.yy = trm.d * 64;
		v.x = trm.e * 64;
		v.y = trm.f * 64;

		fterr = FT_Set_Char_Size(face, 65536, 65536, 72, 72); /* should be 64, 64 */
		if (fterr)
			fz_warn(ctx, "FT_Set_Char_Size(%s,65536,72): %s", font->name, ft_error_string(fterr));
		FT_Set_Transform(face, &m, &v);
		fterr = FT_Load_Glyph(face, gid, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING);
		if (fterr)
		{
			fz_warn(ctx, "FT_Load_Glyph(%s,%d,FT_LOAD_NO_HINTING): %s", font->name, gid, ft_error_string(fterr));
			return NULL;
		}
	}

	if (font->flags.fake_bold)
	{
		FT_Outline_Embolden(&face->glyph->outline, strength * 64);
		FT_Outline_Translate(&face->glyph->outline, -strength * 32, -strength * 32);
	}

	fterr = FT_Render_Glyph(face->glyph, aa > 0 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO);
	if (fterr)
	{
		if (aa > 0)
			fz_warn(ctx, "FT_Render_Glyph(%s,%d,FT_RENDER_MODE_NORMAL): %s", font->name, gid, ft_error_string(fterr));
		else
			fz_warn(ctx, "FT_Render_Glyph(%s,%d,FT_RENDER_MODE_MONO): %s", font->name, gid, ft_error_string(fterr));
		return NULL;
	}
	return face->glyph;
}