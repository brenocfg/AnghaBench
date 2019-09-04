#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_7__ {scalar_t__ seq_keysym; unsigned int modifiers; unsigned int scancode; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ key_translation ;
struct TYPE_6__ {unsigned int remote_modifier_state; int min_keycode; scalar_t__ keymap_loaded; TYPE_2__** keymap; } ;
struct TYPE_8__ {TYPE_1__ xkeymap; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 size_t KEYMAP_MASK ; 
 scalar_t__ MASK_HAS_BITS (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK_REMOVE_BITS (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapCtrlMask ; 
 int /*<<< orphan*/  MapInhibitMask ; 
 void* MapLeftShiftMask ; 
 int /*<<< orphan*/  MapLocalStateMask ; 
 int /*<<< orphan*/  MapShiftMask ; 
 int /*<<< orphan*/  ShiftMask ; 
 int /*<<< orphan*/  get_ksname (size_t) ; 
 int /*<<< orphan*/  warning (char*,size_t,int /*<<< orphan*/ ) ; 

key_translation
xkeymap_translate_key(RDPCLIENT * This, uint32 keysym, unsigned int keycode, unsigned int state)
{
	key_translation tr = { 0, 0, 0, 0 };
	key_translation *ptr;

	ptr = This->xkeymap.keymap[keysym & KEYMAP_MASK];
	if (ptr)
	{
		tr = *ptr;
		if (tr.seq_keysym == 0)	/* Normal scancode translation */
		{
			if (MASK_HAS_BITS(tr.modifiers, MapInhibitMask))
			{
				DEBUG_KBD(("Inhibiting key\n"));
				tr.scancode = 0;
				return tr;
			}

			if (MASK_HAS_BITS(tr.modifiers, MapLocalStateMask))
			{
				/* The modifiers to send for this key should be obtained
				   from the local state. Currently, only shift is implemented. */
				if (MASK_HAS_BITS(state, ShiftMask))
				{
					tr.modifiers = MapLeftShiftMask;
				}
			}

			/* Windows interprets CapsLock+Ctrl+key
			   differently from Shift+Ctrl+key. Since we
			   are simulating CapsLock with Shifts, things
			   like Ctrl+f with CapsLock on breaks. To
			   solve this, we are releasing Shift if Ctrl
			   is on, but only if Shift isn't physically pressed. */
			if (MASK_HAS_BITS(tr.modifiers, MapShiftMask)
			    && MASK_HAS_BITS(This->xkeymap.remote_modifier_state, MapCtrlMask)
			    && !MASK_HAS_BITS(state, ShiftMask))
			{
				DEBUG_KBD(("Non-physical Shift + Ctrl pressed, releasing Shift\n"));
				MASK_REMOVE_BITS(tr.modifiers, MapShiftMask);
			}

			DEBUG_KBD(("Found scancode translation, scancode=0x%x, modifiers=0x%x\n",
				   tr.scancode, tr.modifiers));
		}
	}
	else
	{
		if (This->xkeymap.keymap_loaded)
			warning("No translation for (keysym 0x%lx, %s)\n", keysym,
				get_ksname(keysym));

		/* not in keymap, try to interpret the raw scancode */
		if (((int) keycode >= This->xkeymap.min_keycode) && (keycode <= 0x60))
		{
			tr.scancode = keycode - This->xkeymap.min_keycode;

			/* The modifiers to send for this key should be
			   obtained from the local state. Currently, only
			   shift is implemented. */
			if (MASK_HAS_BITS(state, ShiftMask))
			{
				tr.modifiers = MapLeftShiftMask;
			}

			DEBUG_KBD(("Sending guessed scancode 0x%x\n", tr.scancode));
		}
		else
		{
			DEBUG_KBD(("No good guess for keycode 0x%x found\n", keycode));
		}
	}

	return tr;
}