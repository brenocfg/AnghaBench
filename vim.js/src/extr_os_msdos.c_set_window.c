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
struct TYPE_2__ {int /*<<< orphan*/  screenheight; } ;

/* Variables and functions */
 int /*<<< orphan*/  Columns ; 
 int /*<<< orphan*/  Rows ; 
 TYPE_1__ _video ; 
 int /*<<< orphan*/  mywindow (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_start () ; 
 scalar_t__ term_console ; 

__attribute__((used)) static void
set_window(void)
{
    if (term_console)
    {
#ifndef DJGPP
	_video.screenheight = Rows;
#endif
	mywindow(1, 1, Columns, Rows);
    }
    screen_start();
}