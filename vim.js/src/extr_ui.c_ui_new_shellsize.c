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
struct TYPE_2__ {scalar_t__ in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  exiting ; 
 scalar_t__ full_screen ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  gui_new_shellsize () ; 
 int /*<<< orphan*/  mch_new_shellsize () ; 

void
ui_new_shellsize()
{
    if (full_screen && !exiting)
    {
#ifdef FEAT_GUI
	if (gui.in_use)
	    gui_new_shellsize();
	else
#endif
	    mch_new_shellsize();
    }
}