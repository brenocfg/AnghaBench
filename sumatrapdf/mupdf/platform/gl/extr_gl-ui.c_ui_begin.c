#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  window_h; int /*<<< orphan*/  window_w; scalar_t__ overlay; int /*<<< orphan*/  cursor; TYPE_2__* layout; TYPE_2__* layout_stack; TYPE_1__* cavity; TYPE_1__* cavity_stack; int /*<<< orphan*/ * hot; } ;
struct TYPE_5__ {scalar_t__ pady; scalar_t__ padx; int /*<<< orphan*/  anchor; int /*<<< orphan*/  fill; int /*<<< orphan*/  side; } ;
struct TYPE_4__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; scalar_t__ y0; scalar_t__ x0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  BOTH ; 
 int /*<<< orphan*/  GLUT_CURSOR_INHERIT ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  NW ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glOrtho (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ui ; 

void ui_begin(void)
{
	ui.hot = NULL;

	ui.cavity = ui.cavity_stack;
	ui.cavity->x0 = 0;
	ui.cavity->y0 = 0;
	ui.cavity->x1 = ui.window_w;
	ui.cavity->y1 = ui.window_h;

	ui.layout = ui.layout_stack;
	ui.layout->side = ALL;
	ui.layout->fill = BOTH;
	ui.layout->anchor = NW;
	ui.layout->padx = 0;
	ui.layout->pady = 0;

	ui.cursor = GLUT_CURSOR_INHERIT;

	ui.overlay = 0;

	glViewport(0, 0, ui.window_w, ui.window_h);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, ui.window_w, ui.window_h, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}