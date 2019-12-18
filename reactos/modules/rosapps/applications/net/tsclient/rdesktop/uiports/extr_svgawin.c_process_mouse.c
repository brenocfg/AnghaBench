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
struct TYPE_2__ {int x; int y; } ;

/* Variables and functions */
 int MOUSE_FLAG_BUTTON1 ; 
 int MOUSE_FLAG_BUTTON2 ; 
 int MOUSE_FLAG_BUTTON3 ; 
 int MOUSE_FLAG_DOWN ; 
 int MOUSE_FLAG_MOVE ; 
 int /*<<< orphan*/  RDP_INPUT_MOUSE ; 
 int /*<<< orphan*/  UpAndRunning ; 
 int /*<<< orphan*/  draw_cursor () ; 
 int /*<<< orphan*/  draw_cursor_under (int,int) ; 
 TYPE_1__ mcursor ; 
 int mouse_getbutton () ; 
 int mouse_getx () ; 
 int mouse_gety () ; 
 int mouseb ; 
 int mousex ; 
 int mousey ; 
 int /*<<< orphan*/  rdp_send_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

void process_mouse(void)
{
  int ox = mousex;
  int oy = mousey;
  int ob = mouseb;

  if (!UpAndRunning)
    return;
  mousex = mouse_getx() - mcursor.x;
  mousey = mouse_gety() - mcursor.y;
  mouseb = mouse_getbutton();

  if (mouseb != ob) // button
  {
    // right button
    if (mouseb & 1)
      if (!(ob & 1))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_DOWN | MOUSE_FLAG_BUTTON2,
                       mousex + mcursor.x, mousey + mcursor.y);
    if (ob & 1)
      if (!(mouseb & 1))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_BUTTON2,
                       mousex + mcursor.x, mousey + mcursor.y);
    // middle button
    if (mouseb & 2)
      if (!(ob & 2))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_DOWN | MOUSE_FLAG_BUTTON3,
                       mousex + mcursor.x, mousey + mcursor.y);
    if (ob & 2)
      if (!(mouseb & 2))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_BUTTON3,
                       mousex + mcursor.x, mousey + mcursor.y);
    // left button
    if (mouseb & 4)
      if (!(ob & 4))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_DOWN | MOUSE_FLAG_BUTTON1,
                       mousex + mcursor.x, mousey + mcursor.y);
    if (ob & 4)
      if (!(mouseb & 4))
        rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_BUTTON1,
                       mousex + mcursor.x, mousey + mcursor.y);
  }
  if (mousex != ox || mousey != oy) // movement
  {
    rdp_send_input(0, RDP_INPUT_MOUSE, MOUSE_FLAG_MOVE,
                   mousex + mcursor.x, mousey + mcursor.y);
    draw_cursor_under(ox, oy);
    draw_cursor();
  }
}