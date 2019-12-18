#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  remote_modifier_state; } ;
struct TYPE_11__ {scalar_t__ numlock_sync; TYPE_1__ xkeymap; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 scalar_t__ MASK_HAS_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapLeftAltMask ; 
 int /*<<< orphan*/  MapLeftCtrlMask ; 
 int /*<<< orphan*/  MapLeftShiftMask ; 
 int /*<<< orphan*/  MapRightAltMask ; 
 int /*<<< orphan*/  MapRightCtrlMask ; 
 int /*<<< orphan*/  MapRightShiftMask ; 
 int /*<<< orphan*/  RDP_INPUT_SYNCHRONIZE ; 
 int /*<<< orphan*/  RDP_KEYRELEASE ; 
 int /*<<< orphan*/  SCANCODE_CHAR_LALT ; 
 int /*<<< orphan*/  SCANCODE_CHAR_LCTRL ; 
 int /*<<< orphan*/  SCANCODE_CHAR_LSHIFT ; 
 int /*<<< orphan*/  SCANCODE_CHAR_RALT ; 
 int /*<<< orphan*/  SCANCODE_CHAR_RCTRL ; 
 int /*<<< orphan*/  SCANCODE_CHAR_RSHIFT ; 
 int /*<<< orphan*/  XK_Alt_L ; 
 int /*<<< orphan*/  XK_Alt_R ; 
 int /*<<< orphan*/  XK_Control_L ; 
 int /*<<< orphan*/  XK_Control_R ; 
 int /*<<< orphan*/  XK_ISO_Level3_Shift ; 
 int /*<<< orphan*/  XK_Mode_switch ; 
 int /*<<< orphan*/  XK_Shift_L ; 
 int /*<<< orphan*/  XK_Shift_R ; 
 int /*<<< orphan*/  get_key_state (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_scancode (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_keyboard_state (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_winkey (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_get_numlock_state (TYPE_2__*,unsigned int) ; 

void
reset_modifier_keys(RDPCLIENT * This)
{
	unsigned int state = read_keyboard_state(This);

	/* reset keys */
	uint32 ev_time;
	ev_time = time(NULL);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapLeftShiftMask)
	    && !get_key_state(This, state, XK_Shift_L))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapRightShiftMask)
	    && !get_key_state(This, state, XK_Shift_R))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RSHIFT);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapLeftCtrlMask)
	    && !get_key_state(This, state, XK_Control_L))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LCTRL);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapRightCtrlMask)
	    && !get_key_state(This, state, XK_Control_R))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RCTRL);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapLeftAltMask) && !get_key_state(This, state, XK_Alt_L))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LALT);

	if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapRightAltMask) &&
	    !get_key_state(This, state, XK_Alt_R) && !get_key_state(This, state, XK_Mode_switch)
	    && !get_key_state(This, state, XK_ISO_Level3_Shift))
		rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RALT);

	reset_winkey(This, ev_time);

	if (This->numlock_sync)
		rdp_send_input(This, ev_time, RDP_INPUT_SYNCHRONIZE, 0, ui_get_numlock_state(This, state), 0);
}