#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* font; } ;
typedef  TYPE_2__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int ft_substitute; scalar_t__ ft_stretch; } ;
struct TYPE_8__ {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 TYPE_4__* fz_load_system_cjk_font (int /*<<< orphan*/ *,char const*,int,int) ; 
 unsigned char* fz_lookup_cjk_font (int /*<<< orphan*/ *,int,int*,int*) ; 
 TYPE_4__* fz_new_font_from_memory (int /*<<< orphan*/ *,char const*,unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
pdf_load_substitute_cjk_font(fz_context *ctx, pdf_font_desc *fontdesc, const char *fontname, int ros, int serif)
{
	fontdesc->font = fz_load_system_cjk_font(ctx, fontname, ros, serif);
	if (!fontdesc->font)
	{
		const unsigned char *data;
		int size;
		int subfont;

		data = fz_lookup_cjk_font(ctx, ros, &size, &subfont);
		if (!data)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "cannot find builtin CJK font");

		/* A glyph bbox cache is too big for CJK fonts. */
		fontdesc->font = fz_new_font_from_memory(ctx, fontname, data, size, subfont, 0);
	}

	fontdesc->font->flags.ft_substitute = 1;
	fontdesc->font->flags.ft_stretch = 0;
}