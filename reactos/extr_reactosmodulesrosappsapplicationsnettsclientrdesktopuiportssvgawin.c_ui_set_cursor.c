#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcursor ;
struct TYPE_3__ {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  draw_cursor () ; 
 int /*<<< orphan*/  draw_cursor_under (int,int) ; 
 TYPE_1__ mcursor ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,void*,int) ; 
 int mousex ; 
 int mousey ; 

void ui_set_cursor(void* cursor)
{
  int x;
  int y;
  int ox;
  int oy;

  ox = mousex;
  oy = mousey;
  x = mousex + mcursor.x;
  y = mousey + mcursor.y;
  memcpy(&mcursor, cursor, sizeof(tcursor));
  mousex = x - mcursor.x;
  mousey = y - mcursor.y;
  draw_cursor_under(ox, oy);
  draw_cursor();
}