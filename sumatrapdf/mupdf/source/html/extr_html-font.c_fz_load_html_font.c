#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* custom; } ;
typedef  TYPE_1__ fz_html_font_set ;
struct TYPE_9__ {char* family; int is_bold; int is_italic; int is_small_caps; int /*<<< orphan*/ * font; struct TYPE_9__* next; } ;
typedef  TYPE_2__ fz_html_font_face ;
struct TYPE_10__ {int fake_bold; int fake_italic; int /*<<< orphan*/  is_italic; int /*<<< orphan*/  is_bold; } ;
typedef  TYPE_3__ fz_font_flags_t ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_add_html_font_face (int /*<<< orphan*/ *,TYPE_1__*,char const*,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* fz_font_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_load_html_default_font (int /*<<< orphan*/ *,TYPE_1__*,char const*,int,int) ; 
 unsigned char* fz_lookup_builtin_font (int /*<<< orphan*/ *,char const*,int,int,int*) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

fz_font *
fz_load_html_font(fz_context *ctx, fz_html_font_set *set,
	const char *family, int is_bold, int is_italic, int is_small_caps)
{
	fz_html_font_face *custom;
	const unsigned char *data;
	int best_score = 0;
	fz_font *best_font = NULL;
	int size;

	for (custom = set->custom; custom; custom = custom->next)
	{
		if (!strcmp(family, custom->family))
		{
			int score =
				1 * (is_bold == custom->is_bold) +
				2 * (is_italic == custom->is_italic) +
				4 * (is_small_caps == custom->is_small_caps);
			if (score > best_score)
			{
				best_score = score;
				best_font = custom->font;
			}
		}
	}
	if (best_font)
		return best_font;

	data = fz_lookup_builtin_font(ctx, family, is_bold, is_italic, &size);
	if (data)
	{
		fz_font *font = fz_new_font_from_memory(ctx, NULL, data, size, 0, 0);
		fz_font_flags_t *flags = fz_font_flags(font);
		if (is_bold && !flags->is_bold)
			flags->fake_bold = 1;
		if (is_italic && !flags->is_italic)
			flags->fake_italic = 1;
		fz_add_html_font_face(ctx, set, family, is_bold, is_italic, 0, "<builtin>", font);
		fz_drop_font(ctx, font);
		return font;
	}

	if (!strcmp(family, "monospace") || !strcmp(family, "sans-serif") || !strcmp(family, "serif"))
		return fz_load_html_default_font(ctx, set, family, is_bold, is_italic);

	return NULL;
}