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
struct TYPE_2__ {int x; int y; int down_x; int down_y; int down; int middle_x; int middle_y; int middle; int right_x; int right_y; int right; int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int GLUT_DOWN ; 
#define  GLUT_LEFT_BUTTON 130 
#define  GLUT_MIDDLE_BUTTON 129 
#define  GLUT_RIGHT_BUTTON 128 
 int GLUT_UP ; 
 int /*<<< orphan*/  glutGetModifiers () ; 
 int /*<<< orphan*/  on_wheel (int,int,int,int) ; 
 int /*<<< orphan*/  run_main_loop () ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_invalidate () ; 

__attribute__((used)) static void on_mouse(int button, int action, int x, int y)
{
	ui.x = x;
	ui.y = y;
	if (action == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			ui.down_x = x;
			ui.down_y = y;
			ui.down = 1;
			break;
		case GLUT_MIDDLE_BUTTON:
			ui.middle_x = x;
			ui.middle_y = y;
			ui.middle = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			ui.right_x = x;
			ui.right_y = y;
			ui.right = 1;
			break;
		case 3: on_wheel(0, 1, x, y); break;
		case 4: on_wheel(0, -1, x, y); break;
		case 5: on_wheel(1, 1, x, y); break;
		case 6: on_wheel(1, -1, x, y); break;
		}
	}
	else if (action == GLUT_UP)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: ui.down = 0; break;
		case GLUT_MIDDLE_BUTTON: ui.middle = 0; break;
		case GLUT_RIGHT_BUTTON: ui.right = 0; break;
		}
	}
	ui.mod = glutGetModifiers();
	run_main_loop();
	ui_invalidate(); // TODO: leave this to caller
}