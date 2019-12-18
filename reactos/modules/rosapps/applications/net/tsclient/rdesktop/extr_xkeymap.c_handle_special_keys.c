#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_11__ {int /*<<< orphan*/  numlock_sync; int /*<<< orphan*/  win_button_size; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  RDP_INPUT_SCANCODE ; 
 int /*<<< orphan*/  RDP_INPUT_SYNCHRONIZE ; 
 int /*<<< orphan*/  RDP_KEYPRESS ; 
 int /*<<< orphan*/  RDP_KEYRELEASE ; 
 int SCANCODE_EXTENDED ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XK_Alt_L ; 
 int /*<<< orphan*/  XK_Alt_R ; 
#define  XK_Break 139 
 int /*<<< orphan*/  XK_Control_L ; 
 int /*<<< orphan*/  XK_Control_R ; 
#define  XK_Hyper_L 138 
#define  XK_Hyper_R 137 
#define  XK_Meta_L 136 
#define  XK_Meta_R 135 
#define  XK_Num_Lock 134 
#define  XK_Overlay1_Enable 133 
#define  XK_Pause 132 
#define  XK_Return 131 
#define  XK_Super_L 130 
#define  XK_Super_R 129 
#define  XK_space 128 
 int /*<<< orphan*/  get_key_state (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_scancode (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_keyboard_state (TYPE_1__*) ; 
 int /*<<< orphan*/  send_winkey (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ui_get_numlock_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_seamless_toggle (TYPE_1__*) ; 
 int /*<<< orphan*/  xwin_toggle_fullscreen (TYPE_1__*) ; 

BOOL
handle_special_keys(RDPCLIENT * This, uint32 keysym, unsigned int state, uint32 ev_time, BOOL pressed)
{
	switch (keysym)
	{
		case XK_Return:
			if ((get_key_state(This, state, XK_Alt_L) || get_key_state(This, state, XK_Alt_R))
			    && (get_key_state(This, state, XK_Control_L)
				|| get_key_state(This, state, XK_Control_R)))
			{
				/* Ctrl-Alt-Enter: toggle full screen */
				if (pressed)
					xwin_toggle_fullscreen(This);
				return True;
			}
			break;

		case XK_Break:
			/* Send Break sequence E0 46 E0 C6 */
			if (pressed)
			{
				rdp_send_scancode(This, ev_time, RDP_KEYPRESS,
						  (SCANCODE_EXTENDED | 0x46));
				rdp_send_scancode(This, ev_time, RDP_KEYPRESS,
						  (SCANCODE_EXTENDED | 0xc6));
			}
			/* No release sequence */
			return True;
			break;

		case XK_Pause:
			/* According to MS Keyboard Scan Code
			   Specification, pressing Pause should result
			   in E1 1D 45 E1 9D C5. I'm not exactly sure
			   of how this is supposed to be sent via
			   RDP. The code below seems to work, but with
			   the side effect that Left Ctrl stays
			   down. Therefore, we release it when Pause
			   is released. */
			if (pressed)
			{
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x1d, 0);
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x45, 0);
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xe1, 0);
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0x9d, 0);
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYPRESS, 0xc5, 0);
			}
			else
			{
				/* Release Left Ctrl */
				rdp_send_input(This, ev_time, RDP_INPUT_SCANCODE, RDP_KEYRELEASE,
					       0x1d, 0);
			}
			return True;
			break;

		case XK_Meta_L:	/* Windows keys */
		case XK_Super_L:
		case XK_Hyper_L:
			send_winkey(This, ev_time, pressed, True);
			return True;
			break;

		case XK_Meta_R:
		case XK_Super_R:
		case XK_Hyper_R:
			send_winkey(This, ev_time, pressed, False);
			return True;
			break;

		case XK_space:
			/* Prevent access to the Windows system menu in single app mode */
			if (This->win_button_size
			    && (get_key_state(This, state, XK_Alt_L) || get_key_state(This, state, XK_Alt_R)))
				return True;
			break;

		case XK_Num_Lock:
			/* Synchronize on key release */
			if (This->numlock_sync && !pressed)
				rdp_send_input(This, 0, RDP_INPUT_SYNCHRONIZE, 0,
					       ui_get_numlock_state(This, read_keyboard_state(This)), 0);

			/* Inhibit */
			return True;
			break;
		case XK_Overlay1_Enable:
			/* Toggle SeamlessRDP */
			if (pressed)
				ui_seamless_toggle(This);
			break;

	}
	return False;
}