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
typedef  int /*<<< orphan*/  fz_font ;
struct TYPE_2__ {float fontsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 float fz_advance_glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fz_encode_character_with_fallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_font ; 
 TYPE_1__ ui ; 

float ui_measure_character(int c)
{
	fz_font *font;
	int gid = fz_encode_character_with_fallback(ctx, g_font, c, 0, 0, &font);
	return fz_advance_glyph(ctx, font, gid, 0) * ui.fontsize;
}