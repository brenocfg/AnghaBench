#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ uint16 ;
struct TYPE_9__ {scalar_t__ modifiers; int /*<<< orphan*/  scancode; } ;
typedef  TYPE_2__ key_translation ;
struct TYPE_8__ {scalar_t__ remote_modifier_state; } ;
struct TYPE_10__ {TYPE_1__ xkeymap; int /*<<< orphan*/  numlock_sync; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 scalar_t__ KBD_FLAG_NUMLOCK ; 
 scalar_t__ MASK_HAS_BITS (scalar_t__,scalar_t__) ; 
 scalar_t__ MapAltGrMask ; 
 scalar_t__ MapLeftShiftMask ; 
 scalar_t__ MapNumLockMask ; 
 scalar_t__ MapRightShiftMask ; 
 scalar_t__ MapShiftMask ; 
 int /*<<< orphan*/  RDP_INPUT_SYNCHRONIZE ; 
 int /*<<< orphan*/  RDP_KEYPRESS ; 
 int /*<<< orphan*/  RDP_KEYRELEASE ; 
 int /*<<< orphan*/  SCANCODE_CHAR_LSHIFT ; 
 int /*<<< orphan*/  SCANCODE_CHAR_RALT ; 
 int /*<<< orphan*/  SCANCODE_CHAR_RSHIFT ; 
 scalar_t__ is_modifier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_scancode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ensure_remote_modifiers(RDPCLIENT * This, uint32 ev_time, key_translation tr)
{
	/* If this key is a modifier, do nothing */
	if (is_modifier(tr.scancode))
		return;

	if (!This->numlock_sync)
	{
		/* NumLock */
		if (MASK_HAS_BITS(tr.modifiers, MapNumLockMask)
		    != MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapNumLockMask))
		{
			/* The remote modifier state is not correct */
			uint16 new_remote_state;

			if (MASK_HAS_BITS(tr.modifiers, MapNumLockMask))
			{
				DEBUG_KBD(("Remote NumLock state is incorrect, activating NumLock.\n"));
				new_remote_state = KBD_FLAG_NUMLOCK;
				This->xkeymap.remote_modifier_state = MapNumLockMask;
			}
			else
			{
				DEBUG_KBD(("Remote NumLock state is incorrect, deactivating NumLock.\n"));
				new_remote_state = 0;
				This->xkeymap.remote_modifier_state = 0;
			}

			rdp_send_input(This, 0, RDP_INPUT_SYNCHRONIZE, 0, new_remote_state, 0);
		}
	}


	/* Shift. Left shift and right shift are treated as equal; either is fine. */
	if (MASK_HAS_BITS(tr.modifiers, MapShiftMask)
	    != MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapShiftMask))
	{
		/* The remote modifier state is not correct */
		if (MASK_HAS_BITS(tr.modifiers, MapLeftShiftMask))
		{
			/* Needs left shift. Send down. */
			rdp_send_scancode(This, ev_time, RDP_KEYPRESS, SCANCODE_CHAR_LSHIFT);
		}
		else if (MASK_HAS_BITS(tr.modifiers, MapRightShiftMask))
		{
			/* Needs right shift. Send down. */
			rdp_send_scancode(This, ev_time, RDP_KEYPRESS, SCANCODE_CHAR_RSHIFT);
		}
		else
		{
			/* Should not use this modifier. Send up for shift currently pressed. */
			if (MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapLeftShiftMask))
				/* Left shift is down */
				rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_LSHIFT);
			else
				/* Right shift is down */
				rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RSHIFT);
		}
	}

	/* AltGr */
	if (MASK_HAS_BITS(tr.modifiers, MapAltGrMask)
	    != MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapAltGrMask))
	{
		/* The remote modifier state is not correct */
		if (MASK_HAS_BITS(tr.modifiers, MapAltGrMask))
		{
			/* Needs this modifier. Send down. */
			rdp_send_scancode(This, ev_time, RDP_KEYPRESS, SCANCODE_CHAR_RALT);
		}
		else
		{
			/* Should not use this modifier. Send up. */
			rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, SCANCODE_CHAR_RALT);
		}
	}


}