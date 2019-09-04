#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ seq_keysym; scalar_t__ scancode; struct TYPE_4__* next; } ;
typedef  TYPE_1__ key_translation ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 scalar_t__ False ; 
 int /*<<< orphan*/  RDP_KEYPRESS ; 
 int /*<<< orphan*/  RDP_KEYRELEASE ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  ensure_remote_modifiers (int /*<<< orphan*/ *,scalar_t__,TYPE_1__) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  rdp_send_scancode (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  restore_remote_modifiers (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  save_remote_modifiers (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ xkeymap_translate_key (int /*<<< orphan*/ *,scalar_t__,unsigned int,unsigned int) ; 

void
xkeymap_send_keys(RDPCLIENT * This, uint32 keysym, unsigned int keycode, unsigned int state, uint32 ev_time,
		  BOOL pressed, uint8 nesting)
{
	key_translation tr, *ptr;
	tr = xkeymap_translate_key(This, keysym, keycode, state);

	if (tr.seq_keysym == 0)
	{
		/* Scancode translation */
		if (tr.scancode == 0)
			return;

		if (pressed)
		{
			save_remote_modifiers(This, tr.scancode);
			ensure_remote_modifiers(This, ev_time, tr);
			rdp_send_scancode(This, ev_time, RDP_KEYPRESS, tr.scancode);
			restore_remote_modifiers(This, ev_time, tr.scancode);
		}
		else
		{
			rdp_send_scancode(This, ev_time, RDP_KEYRELEASE, tr.scancode);
		}
		return;
	}

	/* Sequence, only on key down */
	if (pressed)
	{
		ptr = &tr;
		do
		{
			DEBUG_KBD(("Handling sequence element, keysym=0x%x\n",
				   (unsigned int) ptr->seq_keysym));

			if (nesting++ > 32)
			{
				error("Sequence nesting too deep\n");
				return;
			}

			xkeymap_send_keys(This, ptr->seq_keysym, keycode, state, ev_time, True, nesting);
			xkeymap_send_keys(This, ptr->seq_keysym, keycode, state, ev_time, False, nesting);
			ptr = ptr->next;
		}
		while (ptr);
	}
}