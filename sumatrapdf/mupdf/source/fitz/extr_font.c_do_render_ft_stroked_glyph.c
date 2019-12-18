#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {float linewidth; scalar_t__ linejoin; scalar_t__ start_cap; int miterlimit; } ;
typedef  TYPE_3__ fz_stroke_state ;
struct TYPE_31__ {int a; int b; int c; int d; int e; int f; } ;
typedef  TYPE_4__ fz_matrix ;
struct TYPE_28__ {scalar_t__ fake_italic; } ;
struct TYPE_32__ {int /*<<< orphan*/  name; TYPE_1__ flags; TYPE_9__* ft_face; } ;
typedef  TYPE_5__ fz_font ;
struct TYPE_33__ {TYPE_2__* font; } ;
typedef  TYPE_6__ fz_context ;
struct TYPE_36__ {int /*<<< orphan*/  glyph; } ;
struct TYPE_35__ {int xx; int yx; int xy; int yy; } ;
struct TYPE_34__ {int x; int y; } ;
struct TYPE_29__ {int /*<<< orphan*/  ftlib; } ;
typedef  TYPE_7__ FT_Vector ;
typedef  int /*<<< orphan*/  FT_Stroker_LineJoin ;
typedef  int /*<<< orphan*/  FT_Stroker_LineCap ;
typedef  int /*<<< orphan*/  FT_Stroker ;
typedef  TYPE_8__ FT_Matrix ;
typedef  int /*<<< orphan*/ * FT_Glyph ;
typedef  TYPE_9__* FT_Face ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Done_Glyph (int /*<<< orphan*/ *) ; 
 scalar_t__ FT_Get_Glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ FT_Glyph_Stroke (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FT_Glyph_To_Bitmap (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int FT_LOAD_NO_BITMAP ; 
 int FT_LOAD_NO_HINTING ; 
 scalar_t__ FT_Load_Glyph (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  FT_RENDER_MODE_MONO ; 
 int /*<<< orphan*/  FT_RENDER_MODE_NORMAL ; 
 int /*<<< orphan*/  FT_STROKER_LINECAP_BUTT ; 
 int /*<<< orphan*/  FT_STROKER_LINECAP_ROUND ; 
 int /*<<< orphan*/  FT_STROKER_LINECAP_SQUARE ; 
 int /*<<< orphan*/  FT_STROKER_LINEJOIN_BEVEL ; 
 int /*<<< orphan*/  FT_STROKER_LINEJOIN_MITER_FIXED ; 
 int /*<<< orphan*/  FT_STROKER_LINEJOIN_MITER_VARIABLE ; 
 int /*<<< orphan*/  FT_STROKER_LINEJOIN_ROUND ; 
 scalar_t__ FT_Set_Char_Size (TYPE_9__*,int,int,int,int) ; 
 int /*<<< orphan*/  FT_Set_Transform (TYPE_9__*,TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  FT_Stroker_Done (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_Stroker_New (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FT_Stroker_Set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FZ_LINECAP_BUTT ; 
 scalar_t__ FZ_LINECAP_ROUND ; 
 scalar_t__ FZ_LINECAP_SQUARE ; 
 scalar_t__ FZ_LINECAP_TRIANGLE ; 
 scalar_t__ FZ_LINEJOIN_BEVEL ; 
 scalar_t__ FZ_LINEJOIN_MITER ; 
 scalar_t__ FZ_LINEJOIN_ROUND ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  SHEAR ; 
 int /*<<< orphan*/  ft_error_string (scalar_t__) ; 
 int /*<<< orphan*/  fz_adjust_ft_glyph_width (TYPE_6__*,TYPE_5__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 float fz_matrix_expansion (TYPE_4__) ; 
 TYPE_4__ fz_pre_shear (TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (TYPE_6__*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static FT_Glyph
do_render_ft_stroked_glyph(fz_context *ctx, fz_font *font, int gid, fz_matrix trm, fz_matrix ctm, const fz_stroke_state *state, int aa)
{
	FT_Face face = font->ft_face;
	float expansion = fz_matrix_expansion(ctm);
	int linewidth = state->linewidth * expansion * 64 / 2;
	FT_Matrix m;
	FT_Vector v;
	FT_Error fterr;
	FT_Stroker stroker;
	FT_Glyph glyph;
	FT_Stroker_LineJoin line_join;
	FT_Stroker_LineCap line_cap;

	fz_adjust_ft_glyph_width(ctx, font, gid, &trm);

	if (font->flags.fake_italic)
		trm = fz_pre_shear(trm, SHEAR, 0);

	m.xx = trm.a * 64; /* should be 65536 */
	m.yx = trm.b * 64;
	m.xy = trm.c * 64;
	m.yy = trm.d * 64;
	v.x = trm.e * 64;
	v.y = trm.f * 64;

	fz_lock(ctx, FZ_LOCK_FREETYPE);
	fterr = FT_Set_Char_Size(face, 65536, 65536, 72, 72); /* should be 64, 64 */
	if (fterr)
	{
		fz_warn(ctx, "FT_Set_Char_Size(%s,65536,72): %s", font->name, ft_error_string(fterr));
		return NULL;
	}

	FT_Set_Transform(face, &m, &v);

	fterr = FT_Load_Glyph(face, gid, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING);
	if (fterr)
	{
		fz_warn(ctx, "FT_Load_Glyph(%s,%d,FT_LOAD_NO_HINTING): %s", font->name, gid, ft_error_string(fterr));
		return NULL;
	}

	fterr = FT_Stroker_New(ctx->font->ftlib, &stroker);
	if (fterr)
	{
		fz_warn(ctx, "FT_Stroker_New(): %s", ft_error_string(fterr));
		return NULL;
	}

	line_join =
		state->linejoin == FZ_LINEJOIN_MITER ? FT_STROKER_LINEJOIN_MITER_FIXED :
		state->linejoin == FZ_LINEJOIN_ROUND ? FT_STROKER_LINEJOIN_ROUND :
		state->linejoin == FZ_LINEJOIN_BEVEL ? FT_STROKER_LINEJOIN_BEVEL :
		FT_STROKER_LINEJOIN_MITER_VARIABLE;
	line_cap =
		state->start_cap == FZ_LINECAP_BUTT ? FT_STROKER_LINECAP_BUTT :
		state->start_cap == FZ_LINECAP_ROUND ? FT_STROKER_LINECAP_ROUND :
		state->start_cap == FZ_LINECAP_SQUARE ? FT_STROKER_LINECAP_SQUARE :
		state->start_cap == FZ_LINECAP_TRIANGLE ? FT_STROKER_LINECAP_BUTT :
		FT_STROKER_LINECAP_BUTT;

	FT_Stroker_Set(stroker, linewidth, line_cap, line_join, state->miterlimit * 65536);

	fterr = FT_Get_Glyph(face->glyph, &glyph);
	if (fterr)
	{
		fz_warn(ctx, "FT_Get_Glyph(): %s", ft_error_string(fterr));
		FT_Stroker_Done(stroker);
		return NULL;
	}

	fterr = FT_Glyph_Stroke(&glyph, stroker, 1);
	if (fterr)
	{
		fz_warn(ctx, "FT_Glyph_Stroke(): %s", ft_error_string(fterr));
		FT_Done_Glyph(glyph);
		FT_Stroker_Done(stroker);
		return NULL;
	}

	FT_Stroker_Done(stroker);

	fterr = FT_Glyph_To_Bitmap(&glyph, aa > 0 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO, 0, 1);
	if (fterr)
	{
		fz_warn(ctx, "FT_Glyph_To_Bitmap(): %s", ft_error_string(fterr));
		FT_Done_Glyph(glyph);
		return NULL;
	}
	return glyph;
}