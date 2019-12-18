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
struct TYPE_2__ {int x; int y; int key; int mod; int plain; } ;

/* Variables and functions */
 int GLUT_ACTIVE_SHIFT ; 
#define  GLUT_KEY_DELETE 149 
#define  GLUT_KEY_DOWN 148 
#define  GLUT_KEY_END 147 
#define  GLUT_KEY_F1 146 
#define  GLUT_KEY_F10 145 
#define  GLUT_KEY_F11 144 
#define  GLUT_KEY_F12 143 
#define  GLUT_KEY_F2 142 
#define  GLUT_KEY_F3 141 
#define  GLUT_KEY_F4 140 
#define  GLUT_KEY_F5 139 
#define  GLUT_KEY_F6 138 
#define  GLUT_KEY_F7 137 
#define  GLUT_KEY_F8 136 
#define  GLUT_KEY_F9 135 
#define  GLUT_KEY_HOME 134 
#define  GLUT_KEY_INSERT 133 
#define  GLUT_KEY_LEFT 132 
#define  GLUT_KEY_PAGE_DOWN 131 
#define  GLUT_KEY_PAGE_UP 130 
#define  GLUT_KEY_RIGHT 129 
#define  GLUT_KEY_UP 128 
 int KEY_DELETE ; 
 int KEY_DOWN ; 
 int KEY_END ; 
 int KEY_F1 ; 
 int KEY_F10 ; 
 int KEY_F11 ; 
 int KEY_F12 ; 
 int KEY_F2 ; 
 int KEY_F3 ; 
 int KEY_F4 ; 
 int KEY_F5 ; 
 int KEY_F6 ; 
 int KEY_F7 ; 
 int KEY_F8 ; 
 int KEY_F9 ; 
 int KEY_HOME ; 
 int KEY_INSERT ; 
 int KEY_LEFT ; 
 int KEY_PAGE_DOWN ; 
 int KEY_PAGE_UP ; 
 int KEY_RIGHT ; 
 int KEY_UP ; 
 int glutGetModifiers () ; 
 int /*<<< orphan*/  run_main_loop () ; 
 TYPE_1__ ui ; 
 int /*<<< orphan*/  ui_invalidate () ; 

__attribute__((used)) static void on_special(int key, int x, int y)
{
	ui.x = x;
	ui.y = y;
	ui.key = 0;

	switch (key)
	{
	case GLUT_KEY_INSERT: ui.key = KEY_INSERT; break;
#ifdef GLUT_KEY_DELETE
	case GLUT_KEY_DELETE: ui.key = KEY_DELETE; break;
#endif
	case GLUT_KEY_RIGHT: ui.key = KEY_RIGHT; break;
	case GLUT_KEY_LEFT: ui.key = KEY_LEFT; break;
	case GLUT_KEY_DOWN: ui.key = KEY_DOWN; break;
	case GLUT_KEY_UP: ui.key = KEY_UP; break;
	case GLUT_KEY_PAGE_UP: ui.key = KEY_PAGE_UP; break;
	case GLUT_KEY_PAGE_DOWN: ui.key = KEY_PAGE_DOWN; break;
	case GLUT_KEY_HOME: ui.key = KEY_HOME; break;
	case GLUT_KEY_END: ui.key = KEY_END; break;
	case GLUT_KEY_F1: ui.key = KEY_F1; break;
	case GLUT_KEY_F2: ui.key = KEY_F2; break;
	case GLUT_KEY_F3: ui.key = KEY_F3; break;
	case GLUT_KEY_F4: ui.key = KEY_F4; break;
	case GLUT_KEY_F5: ui.key = KEY_F5; break;
	case GLUT_KEY_F6: ui.key = KEY_F6; break;
	case GLUT_KEY_F7: ui.key = KEY_F7; break;
	case GLUT_KEY_F8: ui.key = KEY_F8; break;
	case GLUT_KEY_F9: ui.key = KEY_F9; break;
	case GLUT_KEY_F10: ui.key = KEY_F10; break;
	case GLUT_KEY_F11: ui.key = KEY_F11; break;
	case GLUT_KEY_F12: ui.key = KEY_F12; break;
	}

	if (ui.key)
	{
		ui.mod = glutGetModifiers();
		ui.plain = !(ui.mod & ~GLUT_ACTIVE_SHIFT);
		run_main_loop();
		ui.key = ui.plain = 0;
		ui_invalidate(); // TODO: leave this to caller
	}
}