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
struct TYPE_2__ {scalar_t__ w; scalar_t__ h; } ;

/* Variables and functions */
 scalar_t__ canvas_h ; 
 scalar_t__ canvas_w ; 
 TYPE_1__ page_tex ; 
 scalar_t__ pdf ; 
 int showannotate ; 
 int /*<<< orphan*/  shrinkwrap () ; 

void toggle_annotate(void)
{
	if (pdf)
	{
		showannotate = !showannotate;
		if (canvas_w == page_tex.w && canvas_h == page_tex.h)
			shrinkwrap();
	}
}