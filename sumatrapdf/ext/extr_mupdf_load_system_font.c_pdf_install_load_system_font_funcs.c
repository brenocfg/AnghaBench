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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_install_load_system_font_funcs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_load_windows_cjk_font ; 
 int /*<<< orphan*/  pdf_load_windows_font ; 

void pdf_install_load_system_font_funcs(fz_context *ctx)
{
#ifdef _WIN32
	// TODO(port): also fallback font?
	fz_install_load_system_font_funcs(ctx, pdf_load_windows_font, pdf_load_windows_cjk_font, NULL);
#endif
}