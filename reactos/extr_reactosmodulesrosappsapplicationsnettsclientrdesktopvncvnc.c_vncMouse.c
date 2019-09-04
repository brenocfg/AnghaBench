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
typedef  int /*<<< orphan*/  uint32 ;
struct _rfbClientRec {int dummy; } ;

/* Variables and functions */
 int MOUSE_FLAG_DOWN ; 
 int MOUSE_FLAG_MOVE ; 
 int /*<<< orphan*/  RDP_INPUT_MOUSE ; 
 int lastbuttons ; 
 int* mouseLookup ; 
 int /*<<< orphan*/  rdp_send_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  rfbDefaultPtrAddEvent (int,int,int,struct _rfbClientRec*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
vncMouse(int buttonMask, int x, int y, struct _rfbClientRec *cl)
{
	int b;
	uint32 ev_time = time(NULL);

	rdp_send_input(ev_time, RDP_INPUT_MOUSE, MOUSE_FLAG_MOVE, x, y);

	for (b = 0; b < 3; b++)
	{
		int bb = 1 << (b);
		if (!(lastbuttons & bb) && (buttonMask & bb))
		{
			rdp_send_input(ev_time, RDP_INPUT_MOUSE,
				       (mouseLookup[b]) | MOUSE_FLAG_DOWN, x, y);
		}
		else if ((lastbuttons & bb) && !(buttonMask & bb))
		{
			rdp_send_input(ev_time, RDP_INPUT_MOUSE, (mouseLookup[b]), x, y);
		}
	}
	lastbuttons = buttonMask;

	/* handle cursor */
	rfbDefaultPtrAddEvent(buttonMask, x, y, cl);
}