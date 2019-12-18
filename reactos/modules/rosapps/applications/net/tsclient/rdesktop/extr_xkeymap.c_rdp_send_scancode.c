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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_KBD (char*) ; 
 int KBD_FLAG_EXT ; 
 int /*<<< orphan*/  RDP_INPUT_SCANCODE ; 
 int RDP_KEYRELEASE ; 
 int SCANCODE_EXTENDED ; 
 int /*<<< orphan*/  rdp_send_input (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_modifier_state (int /*<<< orphan*/ *,int,int) ; 

void
rdp_send_scancode(RDPCLIENT * This, uint32 time, uint16 flags, uint8 scancode)
{
	update_modifier_state(This, scancode, !(flags & RDP_KEYRELEASE));

	if (scancode & SCANCODE_EXTENDED)
	{
		DEBUG_KBD(("Sending extended scancode=0x%x, flags=0x%x\n",
			   scancode & ~SCANCODE_EXTENDED, flags));
		rdp_send_input(This, time, RDP_INPUT_SCANCODE, flags | KBD_FLAG_EXT,
			       scancode & ~SCANCODE_EXTENDED, 0);
	}
	else
	{
		DEBUG_KBD(("Sending scancode=0x%x, flags=0x%x\n", scancode, flags));
		rdp_send_input(This, time, RDP_INPUT_SCANCODE, flags, scancode, 0);
	}
}