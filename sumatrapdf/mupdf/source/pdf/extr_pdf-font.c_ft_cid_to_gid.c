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
struct TYPE_7__ {int* cid_to_gid; size_t cid_to_gid_len; TYPE_2__* font; scalar_t__ wmode; scalar_t__ to_ttf_cmap; } ;
typedef  TYPE_3__ pdf_font_desc ;
struct TYPE_5__ {scalar_t__ ft_substitute; } ;
struct TYPE_6__ {int /*<<< orphan*/  ft_face; TYPE_1__ flags; } ;

/* Variables and functions */
 int ft_char_index (int /*<<< orphan*/ ,int) ; 
 int pdf_lookup_cmap (scalar_t__,int) ; 

__attribute__((used)) static int ft_cid_to_gid(pdf_font_desc *fontdesc, int cid)
{
	if (fontdesc->to_ttf_cmap)
	{
		cid = pdf_lookup_cmap(fontdesc->to_ttf_cmap, cid);

		/* vertical presentation forms */
		if (fontdesc->font->flags.ft_substitute && fontdesc->wmode)
		{
			switch (cid)
			{
			case 0x0021: cid = 0xFE15; break; /* ! */
			case 0x0028: cid = 0xFE35; break; /* ( */
			case 0x0029: cid = 0xFE36; break; /* ) */
			case 0x002C: cid = 0xFE10; break; /* , */
			case 0x003A: cid = 0xFE13; break; /* : */
			case 0x003B: cid = 0xFE14; break; /* ; */
			case 0x003F: cid = 0xFE16; break; /* ? */
			case 0x005B: cid = 0xFE47; break; /* [ */
			case 0x005D: cid = 0xFE48; break; /* ] */
			case 0x005F: cid = 0xFE33; break; /* _ */
			case 0x007B: cid = 0xFE37; break; /* { */
			case 0x007D: cid = 0xFE38; break; /* } */
			case 0x2013: cid = 0xFE32; break; /* EN DASH */
			case 0x2014: cid = 0xFE31; break; /* EM DASH */
			case 0x2025: cid = 0xFE30; break; /* TWO DOT LEADER */
			case 0x2026: cid = 0xFE19; break; /* HORIZONTAL ELLIPSIS */
			case 0x3001: cid = 0xFE11; break; /* IDEOGRAPHIC COMMA */
			case 0x3002: cid = 0xFE12; break; /* IDEOGRAPHIC FULL STOP */
			case 0x3008: cid = 0xFE3F; break; /* OPENING ANGLE BRACKET */
			case 0x3009: cid = 0xFE40; break; /* CLOSING ANGLE BRACKET */
			case 0x300A: cid = 0xFE3D; break; /* LEFT DOUBLE ANGLE BRACKET */
			case 0x300B: cid = 0xFE3E; break; /* RIGHT DOUBLE ANGLE BRACKET */
			case 0x300C: cid = 0xFE41; break; /* LEFT CORNER BRACKET */
			case 0x300D: cid = 0xFE42; break; /* RIGHT CORNER BRACKET */
			case 0x300E: cid = 0xFE43; break; /* LEFT WHITE CORNER BRACKET */
			case 0x300F: cid = 0xFE44; break; /* RIGHT WHITE CORNER BRACKET */
			case 0x3010: cid = 0xFE3B; break; /* LEFT BLACK LENTICULAR BRACKET */
			case 0x3011: cid = 0xFE3C; break; /* RIGHT BLACK LENTICULAR BRACKET */
			case 0x3014: cid = 0xFE39; break; /* LEFT TORTOISE SHELL BRACKET */
			case 0x3015: cid = 0xFE3A; break; /* RIGHT TORTOISE SHELL BRACKET */
			case 0x3016: cid = 0xFE17; break; /* LEFT WHITE LENTICULAR BRACKET */
			case 0x3017: cid = 0xFE18; break; /* RIGHT WHITE LENTICULAR BRACKET */

			case 0xFF01: cid = 0xFE15; break; /* FULLWIDTH EXCLAMATION MARK */
			case 0xFF08: cid = 0xFE35; break; /* FULLWIDTH LEFT PARENTHESIS */
			case 0xFF09: cid = 0xFE36; break; /* FULLWIDTH RIGHT PARENTHESIS */
			case 0xFF0C: cid = 0xFE10; break; /* FULLWIDTH COMMA */
			case 0xFF1A: cid = 0xFE13; break; /* FULLWIDTH COLON */
			case 0xFF1B: cid = 0xFE14; break; /* FULLWIDTH SEMICOLON */
			case 0xFF1F: cid = 0xFE16; break; /* FULLWIDTH QUESTION MARK */
			case 0xFF3B: cid = 0xFE47; break; /* FULLWIDTH LEFT SQUARE BRACKET */
			case 0xFF3D: cid = 0xFE48; break; /* FULLWIDTH RIGHT SQUARE BRACKET */
			case 0xFF3F: cid = 0xFE33; break; /* FULLWIDTH LOW LINE */
			case 0xFF5B: cid = 0xFE37; break; /* FULLWIDTH LEFT CURLY BRACKET */
			case 0xFF5D: cid = 0xFE38; break; /* FULLWIDTH RIGHT CURLY BRACKET */

			case 0x30FC: cid = 0xFE31; break; /* KATAKANA-HIRAGANA PROLONGED SOUND MARK */
			case 0xFF0D: cid = 0xFE31; break; /* FULLWIDTH HYPHEN-MINUS */
			}
		}

		return ft_char_index(fontdesc->font->ft_face, cid);
	}

	if (fontdesc->cid_to_gid && (size_t)cid < fontdesc->cid_to_gid_len && cid >= 0)
		return fontdesc->cid_to_gid[cid];

	return cid;
}