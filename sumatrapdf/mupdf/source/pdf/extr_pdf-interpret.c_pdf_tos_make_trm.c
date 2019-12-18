#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {float w; float x; float y; } ;
typedef  TYPE_1__ pdf_vmtx ;
struct TYPE_20__ {int size; int scale; float rise; float char_space; } ;
typedef  TYPE_2__ pdf_text_state ;
struct TYPE_21__ {float char_tx; float char_ty; int cid; int gid; int /*<<< orphan*/  char_bbox; TYPE_5__* fontdesc; int /*<<< orphan*/  tm; } ;
typedef  TYPE_3__ pdf_text_object_state ;
struct TYPE_22__ {float w; } ;
typedef  TYPE_4__ pdf_hmtx ;
struct TYPE_23__ {int wmode; int /*<<< orphan*/  font; } ;
typedef  TYPE_5__ pdf_font_desc ;
struct TYPE_24__ {int a; int d; float f; scalar_t__ e; scalar_t__ c; scalar_t__ b; } ;
typedef  TYPE_6__ fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float fabsf (float) ; 
 int /*<<< orphan*/  fz_bound_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_6__) ; 
 TYPE_6__ fz_concat (TYPE_6__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_expand_rect (int /*<<< orphan*/ ,int) ; 
 int pdf_font_cid_to_gid (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 TYPE_4__ pdf_lookup_hmtx (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 TYPE_1__ pdf_lookup_vmtx (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

int
pdf_tos_make_trm(fz_context *ctx, pdf_text_object_state *tos, pdf_text_state *text, pdf_font_desc *fontdesc, int cid, fz_matrix *trm)
{
	fz_matrix tsm;

	tsm.a = text->size * text->scale;
	tsm.b = 0;
	tsm.c = 0;
	tsm.d = text->size;
	tsm.e = 0;
	tsm.f = text->rise;

	if (fontdesc->wmode == 0)
	{
		pdf_hmtx h = pdf_lookup_hmtx(ctx, fontdesc, cid);
		float w0 = h.w * 0.001f;
		tos->char_tx = (w0 * text->size + text->char_space) * text->scale;
		tos->char_ty = 0;
	}

	if (fontdesc->wmode == 1)
	{
		pdf_vmtx v = pdf_lookup_vmtx(ctx, fontdesc, cid);
		float w1 = v.w * 0.001f;
		tsm.e -= v.x * fabsf(text->size) * 0.001f;
		tsm.f -= v.y * text->size * 0.001f;
		tos->char_tx = 0;
		tos->char_ty = w1 * text->size + text->char_space;
	}

	*trm = fz_concat(tsm, tos->tm);

	tos->cid = cid;
	tos->gid = pdf_font_cid_to_gid(ctx, fontdesc, cid);
	tos->fontdesc = fontdesc;

	/* Compensate for the glyph cache limited positioning precision */
	tos->char_bbox = fz_expand_rect(fz_bound_glyph(ctx, fontdesc->font, tos->gid, *trm), 1);

	return tos->gid;
}