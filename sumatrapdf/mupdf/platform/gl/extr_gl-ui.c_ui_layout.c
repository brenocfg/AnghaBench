#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum side { ____Placeholder_side } side ;
typedef  enum fill { ____Placeholder_fill } fill ;
typedef  enum anchor { ____Placeholder_anchor } anchor ;
struct TYPE_4__ {TYPE_1__* layout; } ;
struct TYPE_3__ {int side; int fill; int anchor; int padx; int pady; } ;

/* Variables and functions */
 TYPE_2__ ui ; 

void ui_layout(enum side side, enum fill fill, enum anchor anchor, int padx, int pady)
{
	ui.layout->side = side;
	ui.layout->fill = fill;
	ui.layout->anchor = anchor;
	ui.layout->padx = padx;
	ui.layout->pady = pady;
}