#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_load_system_font_fn ;
typedef  int /*<<< orphan*/  fz_load_system_fallback_font_fn ;
typedef  int /*<<< orphan*/  fz_load_system_cjk_font_fn ;
struct TYPE_5__ {TYPE_1__* font; } ;
typedef  TYPE_2__ fz_context ;
struct TYPE_4__ {int /*<<< orphan*/ * load_fallback_font; int /*<<< orphan*/ * load_cjk_font; int /*<<< orphan*/ * load_font; } ;

/* Variables and functions */

void fz_install_load_system_font_funcs(fz_context *ctx,
		fz_load_system_font_fn *f,
		fz_load_system_cjk_font_fn *f_cjk,
		fz_load_system_fallback_font_fn *f_back)
{
	ctx->font->load_font = f;
	ctx->font->load_cjk_font = f_cjk;
	ctx->font->load_fallback_font = f_back;
}