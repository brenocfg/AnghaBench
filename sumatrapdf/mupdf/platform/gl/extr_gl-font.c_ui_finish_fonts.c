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

/* Variables and functions */
 int /*<<< orphan*/  clear_font_cache () ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_drop_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_font ; 

void ui_finish_fonts(void)
{
	clear_font_cache();
	fz_drop_font(ctx, g_font);
}