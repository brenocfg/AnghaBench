#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {float x0; float x1; float y0; float y1; } ;
typedef  TYPE_3__ fz_rect ;
struct TYPE_27__ {int a; int b; int c; int d; int e; int f; } ;
typedef  TYPE_4__ fz_matrix ;
struct TYPE_24__ {scalar_t__ fake_bold; scalar_t__ fake_italic; } ;
struct TYPE_28__ {TYPE_1__ flags; int /*<<< orphan*/  name; TYPE_3__* bbox_table; TYPE_8__* ft_face; } ;
typedef  TYPE_5__ fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_32__ {float const xMin; float const yMin; float const xMax; float const yMax; } ;
struct TYPE_31__ {int units_per_EM; TYPE_2__* glyph; } ;
struct TYPE_30__ {int xx; int yx; int xy; int yy; } ;
struct TYPE_29__ {int x; int y; } ;
struct TYPE_25__ {int /*<<< orphan*/  outline; } ;
typedef  TYPE_6__ FT_Vector ;
typedef  TYPE_7__ FT_Matrix ;
typedef  TYPE_8__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  TYPE_9__ FT_BBox ;

/* Variables and functions */
 int FT_LOAD_NO_BITMAP ; 
 int FT_LOAD_NO_HINTING ; 
 scalar_t__ FT_Load_Glyph (TYPE_8__*,int,int) ; 
 int /*<<< orphan*/  FT_Outline_Embolden (int /*<<< orphan*/ *,float const) ; 
 int /*<<< orphan*/  FT_Outline_Get_CBox (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  FT_Outline_Translate (int /*<<< orphan*/ *,float const,float const) ; 
 scalar_t__ FT_Set_Char_Size (TYPE_8__*,int const,int const,int,int) ; 
 int /*<<< orphan*/  FT_Set_Transform (TYPE_8__*,TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  SHEAR ; 
 int /*<<< orphan*/  ft_error_string (scalar_t__) ; 
 int /*<<< orphan*/  fz_adjust_ft_glyph_width (int /*<<< orphan*/ *,TYPE_5__*,int,TYPE_4__*) ; 
 TYPE_4__ fz_identity ; 
 scalar_t__ fz_is_empty_rect (TYPE_3__) ; 
 int /*<<< orphan*/  fz_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ fz_pre_shear (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_rect *
fz_bound_ft_glyph(fz_context *ctx, fz_font *font, int gid)
{
	FT_Face face = font->ft_face;
	FT_Error fterr;
	FT_BBox cbox;
	FT_Matrix m;
	FT_Vector v;
	fz_rect *bounds = &font->bbox_table[gid];

	// TODO: refactor loading into fz_load_ft_glyph
	// TODO: cache results

	const int scale = face->units_per_EM;
	const float recip = 1.0f / scale;
	const float strength = 0.02f;
	fz_matrix trm = fz_identity;

	fz_adjust_ft_glyph_width(ctx, font, gid, &trm);

	if (font->flags.fake_italic)
		trm = fz_pre_shear(trm, SHEAR, 0);

	m.xx = trm.a * 65536;
	m.yx = trm.b * 65536;
	m.xy = trm.c * 65536;
	m.yy = trm.d * 65536;
	v.x = trm.e * 65536;
	v.y = trm.f * 65536;

	fz_lock(ctx, FZ_LOCK_FREETYPE);
	/* Set the char size to scale=face->units_per_EM to effectively give
	 * us unscaled results. This avoids quantisation. We then apply the
	 * scale ourselves below. */
	fterr = FT_Set_Char_Size(face, scale, scale, 72, 72);
	if (fterr)
		fz_warn(ctx, "FT_Set_Char_Size(%s,%d,72): %s", font->name, scale, ft_error_string(fterr));
	FT_Set_Transform(face, &m, &v);

	fterr = FT_Load_Glyph(face, gid, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING);
	if (fterr)
	{
		fz_warn(ctx, "FT_Load_Glyph(%s,%d,FT_LOAD_NO_HINTING): %s", font->name, gid, ft_error_string(fterr));
		fz_unlock(ctx, FZ_LOCK_FREETYPE);
		bounds->x0 = bounds->x1 = trm.e;
		bounds->y0 = bounds->y1 = trm.f;
		return bounds;
	}

	if (font->flags.fake_bold)
	{
		FT_Outline_Embolden(&face->glyph->outline, strength * scale);
		FT_Outline_Translate(&face->glyph->outline, -strength * 0.5f * scale, -strength * 0.5f * scale);
	}

	FT_Outline_Get_CBox(&face->glyph->outline, &cbox);
	fz_unlock(ctx, FZ_LOCK_FREETYPE);
	bounds->x0 = cbox.xMin * recip;
	bounds->y0 = cbox.yMin * recip;
	bounds->x1 = cbox.xMax * recip;
	bounds->y1 = cbox.yMax * recip;

	if (fz_is_empty_rect(*bounds))
	{
		bounds->x0 = bounds->x1 = trm.e;
		bounds->y0 = bounds->y1 = trm.f;
	}

	return bounds;
}