#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint16 ;
struct TYPE_4__ {scalar_t__ remote_modifier_state; } ;
struct TYPE_5__ {TYPE_1__ xkeymap; int /*<<< orphan*/  numlock_sync; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  MASK_CHANGE_BIT (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MASK_HAS_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapLeftAltMask ; 
 int /*<<< orphan*/  MapLeftCtrlMask ; 
 int /*<<< orphan*/  MapLeftShiftMask ; 
 int /*<<< orphan*/  MapLeftWinMask ; 
 int /*<<< orphan*/  MapNumLockMask ; 
 int /*<<< orphan*/  MapRightAltMask ; 
 int /*<<< orphan*/  MapRightCtrlMask ; 
 int /*<<< orphan*/  MapRightShiftMask ; 
 int /*<<< orphan*/  MapRightWinMask ; 
#define  SCANCODE_CHAR_LALT 136 
#define  SCANCODE_CHAR_LCTRL 135 
#define  SCANCODE_CHAR_LSHIFT 134 
#define  SCANCODE_CHAR_LWIN 133 
#define  SCANCODE_CHAR_NUMLOCK 132 
#define  SCANCODE_CHAR_RALT 131 
#define  SCANCODE_CHAR_RCTRL 130 
#define  SCANCODE_CHAR_RSHIFT 129 
#define  SCANCODE_CHAR_RWIN 128 

__attribute__((used)) static void
update_modifier_state(RDPCLIENT * This, uint8 scancode, BOOL pressed)
{
#ifdef WITH_DEBUG_KBD
	uint16 old_modifier_state;

	old_modifier_state = This->xkeymap.remote_modifier_state;
#endif

	switch (scancode)
	{
		case SCANCODE_CHAR_LSHIFT:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapLeftShiftMask, pressed);
			break;
		case SCANCODE_CHAR_RSHIFT:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapRightShiftMask, pressed);
			break;
		case SCANCODE_CHAR_LCTRL:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapLeftCtrlMask, pressed);
			break;
		case SCANCODE_CHAR_RCTRL:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapRightCtrlMask, pressed);
			break;
		case SCANCODE_CHAR_LALT:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapLeftAltMask, pressed);
			break;
		case SCANCODE_CHAR_RALT:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapRightAltMask, pressed);
			break;
		case SCANCODE_CHAR_LWIN:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapLeftWinMask, pressed);
			break;
		case SCANCODE_CHAR_RWIN:
			MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state, MapRightWinMask, pressed);
			break;
		case SCANCODE_CHAR_NUMLOCK:
			/* KeyReleases for NumLocks are sent immediately. Toggle the
			   modifier state only on Keypress */
			if (pressed && !This->numlock_sync)
			{
				BOOL newNumLockState;
				newNumLockState =
					(MASK_HAS_BITS
					 (This->xkeymap.remote_modifier_state, MapNumLockMask) == False);
				MASK_CHANGE_BIT(This->xkeymap.remote_modifier_state,
						MapNumLockMask, newNumLockState);
			}
	}

#ifdef WITH_DEBUG_KBD
	if (old_modifier_state != This->xkeymap.remote_modifier_state)
	{
		DEBUG_KBD(("Before updating modifier_state:0x%x, pressed=0x%x\n",
			   old_modifier_state, pressed));
		DEBUG_KBD(("After updating modifier_state:0x%x\n", This->xkeymap.remote_modifier_state));
	}
#endif

}