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
typedef  int /*<<< orphan*/  fz_font ;
struct TYPE_9__ {TYPE_1__* font; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_10__ {int /*<<< orphan*/ * sans; int /*<<< orphan*/ * serif; } ;
struct TYPE_8__ {TYPE_3__* fallback; } ;

/* Variables and functions */
#define  FZ_LANG_ja 131 
#define  FZ_LANG_ko 130 
 int FZ_LANG_ur ; 
 int FZ_LANG_urd ; 
#define  FZ_LANG_zh_Hans 129 
#define  FZ_LANG_zh_Hant 128 
 int UCDN_LAST_SCRIPT ; 
 int UCDN_SCRIPT_ARABIC ; 
 int UCDN_SCRIPT_HAN ; 
 int /*<<< orphan*/ * fz_load_system_fallback_font (TYPE_2__*,int,int,int,int,int) ; 
 unsigned char* fz_lookup_noto_font (TYPE_2__*,int,int,int*,int*) ; 
 int /*<<< orphan*/ * fz_new_font_from_memory (TYPE_2__*,int /*<<< orphan*/ *,unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nelem (TYPE_3__*) ; 

fz_font *fz_load_fallback_font(fz_context *ctx, int script, int language, int serif, int bold, int italic)
{
	fz_font **fontp;
	const unsigned char *data;
	int index;
	int subfont;
	int size;

	if (script < 0 || script >= (int)nelem(ctx->font->fallback))
		return NULL;

	/* TODO: bold and italic */

	index = script;
	if (script == UCDN_SCRIPT_HAN)
	{
		switch (language)
		{
		case FZ_LANG_ja: index = UCDN_LAST_SCRIPT + 1; break;
		case FZ_LANG_ko: index = UCDN_LAST_SCRIPT + 2; break;
		case FZ_LANG_zh_Hans: index = UCDN_LAST_SCRIPT + 3; break;
		case FZ_LANG_zh_Hant: index = UCDN_LAST_SCRIPT + 4; break;
		}
	}
	if (script == UCDN_SCRIPT_ARABIC)
	{
		if (language == FZ_LANG_ur || language == FZ_LANG_urd)
			index = UCDN_LAST_SCRIPT + 5;
	}

	if (serif)
		fontp = &ctx->font->fallback[index].serif;
	else
		fontp = &ctx->font->fallback[index].sans;

	if (!*fontp)
	{
		*fontp = fz_load_system_fallback_font(ctx, script, language, serif, bold, italic);
		if (!*fontp)
		{
			data = fz_lookup_noto_font(ctx, script, language, &size, &subfont);
			if (data)
				*fontp = fz_new_font_from_memory(ctx, NULL, data, size, subfont, 0);
		}
	}

	return *fontp;
}