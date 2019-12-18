#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ftlib_refs; int /*<<< orphan*/ * ftlib; } ;
typedef  TYPE_1__ fz_font_context ;
struct TYPE_8__ {TYPE_1__* font; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int FT_Done_Library (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FZ_LOCK_FREETYPE ; 
 int /*<<< orphan*/  ft_error_string (int) ; 
 int /*<<< orphan*/  fz_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_warn (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_drop_freetype(fz_context *ctx)
{
	int fterr;
	fz_font_context *fct = ctx->font;

	fz_lock(ctx, FZ_LOCK_FREETYPE);
	if (--fct->ftlib_refs == 0)
	{
		fterr = FT_Done_Library(fct->ftlib);
		if (fterr)
			fz_warn(ctx, "FT_Done_Library(): %s", ft_error_string(fterr));
		fct->ftlib = NULL;
	}
	fz_unlock(ctx, FZ_LOCK_FREETYPE);
}