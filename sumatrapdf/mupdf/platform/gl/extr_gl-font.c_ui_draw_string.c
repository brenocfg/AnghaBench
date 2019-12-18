#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ baseline; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_begin_text () ; 
 scalar_t__ ui_draw_character_imp (float,scalar_t__,int) ; 
 int /*<<< orphan*/  ui_end_text () ; 

void ui_draw_string(float x, float y, const char *str)
{
	int c;
	ui_begin_text();
	while (*str)
	{
		str += fz_chartorune(&c, str);
		x += ui_draw_character_imp(x, y + ui.baseline, c);
	}
	ui_end_text();
}