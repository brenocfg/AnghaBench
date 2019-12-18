#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_text_language ;
typedef  int /*<<< orphan*/  fz_text ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_bidi_direction ;

/* Variables and functions */
 float fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int fz_encode_character_with_fallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fz_pre_translate (int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/  fz_show_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fz_matrix
fz_show_string(fz_context *ctx, fz_text *text, fz_font *user_font, fz_matrix trm, const char *s, int wmode, int bidi_level, fz_bidi_direction markup_dir, fz_text_language language)
{
	fz_font *font;
	int gid, ucs;
	float adv;

	while (*s)
	{
		s += fz_chartorune(&ucs, s);
		gid = fz_encode_character_with_fallback(ctx, user_font, ucs, 0, language, &font);
		fz_show_glyph(ctx, text, font, trm, gid, ucs, wmode, bidi_level, markup_dir, language);
		adv = fz_advance_glyph(ctx, font, gid, wmode);
		if (wmode == 0)
			trm = fz_pre_translate(trm, adv, 0);
		else
			trm = fz_pre_translate(trm, 0, -adv);
	}

	return trm;
}