#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_font ;
struct TYPE_9__ {TYPE_1__* font; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_8__ {int /*<<< orphan*/ * cjk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fz_keep_font (TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned char* fz_lookup_cjk_font (TYPE_2__*,int,int*,int*) ; 
 int /*<<< orphan*/  fz_new_font_from_memory (TYPE_2__*,int /*<<< orphan*/ *,unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nelem (int /*<<< orphan*/ *) ; 

fz_font *
fz_new_cjk_font(fz_context *ctx, int ordering)
{
	const unsigned char *data;
	int size, index;
	if (ordering >= 0 && ordering < (int)nelem(ctx->font->cjk))
	{
		if (ctx->font->cjk[ordering])
			return fz_keep_font(ctx, ctx->font->cjk[ordering]);
		data = fz_lookup_cjk_font(ctx, ordering, &size, &index);
		if (data)
		{
			ctx->font->cjk[ordering] = fz_new_font_from_memory(ctx, NULL, data, size, index, 0);
			return fz_keep_font(ctx, ctx->font->cjk[ordering]);
		}
	}
	fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find builtin CJK font");
}