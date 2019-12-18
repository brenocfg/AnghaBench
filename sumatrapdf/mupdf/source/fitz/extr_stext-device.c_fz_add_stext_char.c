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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ fz_stext_device ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_STEXT_PRESERVE_LIGATURES ; 
 int FZ_STEXT_PRESERVE_WHITESPACE ; 
 int /*<<< orphan*/  fz_add_stext_char_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,float,int) ; 

__attribute__((used)) static void
fz_add_stext_char(fz_context *ctx, fz_stext_device *dev, fz_font *font, int c, int glyph, fz_matrix trm, float adv, int wmode)
{
	/* ignore when one unicode character maps to multiple glyphs */
	if (c == -1)
		return;

	if (!(dev->flags & FZ_STEXT_PRESERVE_LIGATURES))
	{
		switch (c)
		{
		case 0xFB00: /* ff */
			fz_add_stext_char_imp(ctx, dev, font, 'f', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'f', -1, trm, 0, wmode);
			return;
		case 0xFB01: /* fi */
			fz_add_stext_char_imp(ctx, dev, font, 'f', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'i', -1, trm, 0, wmode);
			return;
		case 0xFB02: /* fl */
			fz_add_stext_char_imp(ctx, dev, font, 'f', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'l', -1, trm, 0, wmode);
			return;
		case 0xFB03: /* ffi */
			fz_add_stext_char_imp(ctx, dev, font, 'f', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'f', -1, trm, 0, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'i', -1, trm, 0, wmode);
			return;
		case 0xFB04: /* ffl */
			fz_add_stext_char_imp(ctx, dev, font, 'f', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'f', -1, trm, 0, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 'l', -1, trm, 0, wmode);
			return;
		case 0xFB05: /* long st */
		case 0xFB06: /* st */
			fz_add_stext_char_imp(ctx, dev, font, 's', glyph, trm, adv, wmode);
			fz_add_stext_char_imp(ctx, dev, font, 't', -1, trm, 0, wmode);
			return;
		}
	}

	if (!(dev->flags & FZ_STEXT_PRESERVE_WHITESPACE))
	{
		switch (c)
		{
		case 0x0009: /* tab */
		case 0x0020: /* space */
		case 0x00A0: /* no-break space */
		case 0x1680: /* ogham space mark */
		case 0x180E: /* mongolian vowel separator */
		case 0x2000: /* en quad */
		case 0x2001: /* em quad */
		case 0x2002: /* en space */
		case 0x2003: /* em space */
		case 0x2004: /* three-per-em space */
		case 0x2005: /* four-per-em space */
		case 0x2006: /* six-per-em space */
		case 0x2007: /* figure space */
		case 0x2008: /* punctuation space */
		case 0x2009: /* thin space */
		case 0x200A: /* hair space */
		case 0x202F: /* narrow no-break space */
		case 0x205F: /* medium mathematical space */
		case 0x3000: /* ideographic space */
			c = ' ';
		}
	}

	fz_add_stext_char_imp(ctx, dev, font, c, glyph, trm, adv, wmode);
}