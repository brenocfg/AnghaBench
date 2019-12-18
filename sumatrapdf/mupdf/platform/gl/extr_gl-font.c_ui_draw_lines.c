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
struct line {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_2__ {scalar_t__ lineheight; } ;

/* Variables and functions */
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_draw_string_part (float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ui_draw_lines(float x, float y, struct line *lines, int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		ui_draw_string_part(x, y, lines[i].a, lines[i].b);
		y += ui.lineheight;
	}
}