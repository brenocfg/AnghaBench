#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* height; void* width; void* font_size; int /*<<< orphan*/  list_style_type; int /*<<< orphan*/  white_space; int /*<<< orphan*/  vertical_align; int /*<<< orphan*/  text_align; int /*<<< orphan*/  visibility; } ;
typedef  TYPE_1__ fz_css_style ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  LST_DISC ; 
 int /*<<< orphan*/  N_AUTO ; 
 int /*<<< orphan*/  N_SCALE ; 
 int /*<<< orphan*/  TA_LEFT ; 
 int /*<<< orphan*/  VA_BASELINE ; 
 int /*<<< orphan*/  V_VISIBLE ; 
 int /*<<< orphan*/  WS_NORMAL ; 
 void* make_number (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
fz_default_css_style(fz_context *ctx, fz_css_style *style)
{
	memset(style, 0, sizeof *style);
	style->visibility = V_VISIBLE;
	style->text_align = TA_LEFT;
	style->vertical_align = VA_BASELINE;
	style->white_space = WS_NORMAL;
	style->list_style_type = LST_DISC;
	style->font_size = make_number(1, N_SCALE);
	style->width = make_number(0, N_AUTO);
	style->height = make_number(0, N_AUTO);
}