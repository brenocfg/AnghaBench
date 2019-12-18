#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int text_mode; int /*<<< orphan*/  text; } ;
struct TYPE_13__ {int gtop; TYPE_4__ tos; int /*<<< orphan*/  default_cs; int /*<<< orphan*/  dev; TYPE_2__* gstate; } ;
typedef  TYPE_1__ pdf_run_processor ;
struct TYPE_17__ {int render; TYPE_3__* font; } ;
struct TYPE_14__ {int /*<<< orphan*/  ctm; TYPE_7__ text; } ;
typedef  TYPE_2__ pdf_gstate ;
struct TYPE_15__ {size_t cid_to_ucs_len; int* cid_to_ucs; int /*<<< orphan*/  wmode; int /*<<< orphan*/  font; scalar_t__ to_unicode; } ;
typedef  TYPE_3__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_BIDI_NEUTRAL ; 
 int /*<<< orphan*/  FZ_LANG_UNSET ; 
 int FZ_REPLACEMENT_CHARACTER ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_glyph_cacheable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_render_t3_glyph_direct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_show_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* pdf_flush_text (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int pdf_lookup_cmap_full (scalar_t__,int,int*) ; 
 int pdf_tos_make_trm (int /*<<< orphan*/ *,TYPE_4__*,TYPE_7__*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_tos_move_after_char (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  pdf_tos_reset (int /*<<< orphan*/ *,TYPE_4__*,int) ; 

__attribute__((used)) static void
pdf_show_char(fz_context *ctx, pdf_run_processor *pr, int cid)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_font_desc *fontdesc = gstate->text.font;
	fz_matrix trm;
	int gid;
	int ucsbuf[8];
	int ucslen;
	int i;
	int render_direct;

	gid = pdf_tos_make_trm(ctx, &pr->tos, &gstate->text, fontdesc, cid, &trm);

	/* If we are uncachable, then render direct. */
	render_direct = !fz_glyph_cacheable(ctx, fontdesc->font, gid);

	/* flush buffered text if rendermode has changed */
	if (!pr->tos.text || gstate->text.render != pr->tos.text_mode || render_direct)
	{
		gstate = pdf_flush_text(ctx, pr);
		pdf_tos_reset(ctx, &pr->tos, gstate->text.render);
	}

	if (render_direct)
	{
		/* Render the glyph stream direct here (only happens for
		 * type3 glyphs that seem to inherit current graphics
		 * attributes, or type 3 glyphs within type3 glyphs). */
		fz_matrix composed = fz_concat(trm, gstate->ctm);
		fz_render_t3_glyph_direct(ctx, pr->dev, fontdesc->font, gid, composed, gstate, pr->default_cs);
		/* Render text invisibly so that it can still be extracted. */
		pr->tos.text_mode = 3;
	}

	ucslen = 0;
	if (fontdesc->to_unicode)
		ucslen = pdf_lookup_cmap_full(fontdesc->to_unicode, cid, ucsbuf);
	if (ucslen == 0 && (size_t)cid < fontdesc->cid_to_ucs_len)
	{
		ucsbuf[0] = fontdesc->cid_to_ucs[cid];
		ucslen = 1;
	}
	if (ucslen == 0 || (ucslen == 1 && ucsbuf[0] == 0))
	{
		ucsbuf[0] = FZ_REPLACEMENT_CHARACTER;
		ucslen = 1;
	}

	/* add glyph to textobject */
	fz_show_glyph(ctx, pr->tos.text, fontdesc->font, trm, gid, ucsbuf[0], fontdesc->wmode, 0, FZ_BIDI_NEUTRAL, FZ_LANG_UNSET);

	/* add filler glyphs for one-to-many unicode mapping */
	for (i = 1; i < ucslen; i++)
		fz_show_glyph(ctx, pr->tos.text, fontdesc->font, trm, -1, ucsbuf[i], fontdesc->wmode, 0, FZ_BIDI_NEUTRAL, FZ_LANG_UNSET);

	pdf_tos_move_after_char(ctx, &pr->tos);
}