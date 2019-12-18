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
struct TYPE_2__ {int w; int h; } ;

/* Variables and functions */
 int annotate_w ; 
 int /*<<< orphan*/  glutReshapeWindow (int,int) ; 
 scalar_t__ isfullscreen ; 
 int outline_w ; 
 TYPE_1__ page_tex ; 
 int screen_h ; 
 int screen_w ; 
 scalar_t__ showannotate ; 
 scalar_t__ showoutline ; 
 int /*<<< orphan*/  toggle_fullscreen () ; 

__attribute__((used)) static void shrinkwrap(void)
{
	int w = page_tex.w + (showoutline ? outline_w + 4 : 0) + (showannotate ? annotate_w : 0);
	int h = page_tex.h;
	if (screen_w > 0 && w > screen_w)
		w = screen_w;
	if (screen_h > 0 && h > screen_h)
		h = screen_h;
	if (isfullscreen)
		toggle_fullscreen();
	glutReshapeWindow(w, h);
}