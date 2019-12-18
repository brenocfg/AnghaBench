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
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_4__ {TYPE_1__* layout; int /*<<< orphan*/ * cavity; } ;
struct TYPE_3__ {scalar_t__ pady; scalar_t__ padx; int /*<<< orphan*/  anchor; int /*<<< orphan*/  fill; int /*<<< orphan*/  side; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  NW ; 
 TYPE_2__ ui ; 

void ui_pack_push(fz_irect cavity)
{
	*(++ui.cavity) = cavity;
	++ui.layout;
	ui.layout->side = ALL;
	ui.layout->fill = BOTH;
	ui.layout->anchor = NW;
	ui.layout->padx = 0;
	ui.layout->pady = 0;
}