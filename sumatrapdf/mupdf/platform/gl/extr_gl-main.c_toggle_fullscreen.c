#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  GLUT_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  GLUT_WINDOW_WIDTH ; 
 int /*<<< orphan*/  GLUT_WINDOW_X ; 
 int /*<<< orphan*/  GLUT_WINDOW_Y ; 
 int /*<<< orphan*/  glutFullScreen () ; 
 int glutGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutPositionWindow (int,int) ; 
 int /*<<< orphan*/  glutReshapeWindow (int,int) ; 
 int isfullscreen ; 

__attribute__((used)) static void toggle_fullscreen(void)
{
	static int win_x = 0, win_y = 0;
	static int win_w = 100, win_h = 100;
	if (!isfullscreen)
	{
		win_w = glutGet(GLUT_WINDOW_WIDTH);
		win_h = glutGet(GLUT_WINDOW_HEIGHT);
		win_x = glutGet(GLUT_WINDOW_X);
		win_y = glutGet(GLUT_WINDOW_Y);
		glutFullScreen();
		isfullscreen = 1;
	}
	else
	{
		glutPositionWindow(win_x, win_y);
		glutReshapeWindow(win_w, win_h);
		isfullscreen = 0;
	}
}