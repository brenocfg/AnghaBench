#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_12__ {scalar_t__ use_rdp5; int /*<<< orphan*/  rdp_shareid; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  RDP_CTL_COOPERATE ; 
 int /*<<< orphan*/  RDP_CTL_REQUEST_CONTROL ; 
 int /*<<< orphan*/  RDP_INPUT_SYNCHRONIZE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_enum_bmpcache2 (TYPE_1__*) ; 
 int /*<<< orphan*/  rdp_process_server_caps (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_recv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_send_confirm_active (TYPE_1__*) ; 
 int /*<<< orphan*/  rdp_send_control (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_fonts (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rdp_send_input (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdp_send_synchronise (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_order_state (TYPE_1__*) ; 

__attribute__((used)) static BOOL
process_demand_active(RDPCLIENT * This, STREAM s)
{
	uint8 type;
	uint16 len_src_descriptor, len_combined_caps;

	in_uint32_le(s, This->rdp_shareid);
	in_uint16_le(s, len_src_descriptor);
	in_uint16_le(s, len_combined_caps);
	in_uint8s(s, len_src_descriptor);

	DEBUG(("DEMAND_ACTIVE(id=0x%x)\n", This->rdp_shareid));
	rdp_process_server_caps(This, s, len_combined_caps);

	if
	(
		!rdp_send_confirm_active(This) ||
		!rdp_send_synchronise(This) ||
		!rdp_send_control(This, RDP_CTL_COOPERATE) ||
		!rdp_send_control(This, RDP_CTL_REQUEST_CONTROL) ||
		!rdp_recv(This, &type) ||	/* RDP_PDU_SYNCHRONIZE */
		!rdp_recv(This, &type) ||	/* RDP_CTL_COOPERATE */
		!rdp_recv(This, &type) ||	/* RDP_CTL_GRANT_CONTROL */
		!rdp_send_input(This, 0, RDP_INPUT_SYNCHRONIZE, 0,
				   /*This->numlock_sync ? ui_get_numlock_state(This, read_keyboard_state(This)) :*/ 0, 0) // TODO: keyboard mess
	)
		return False;

	if (This->use_rdp5)
	{
		if(!rdp_enum_bmpcache2(This) || !rdp_send_fonts(This, 3))
			return False;
	}
	else
	{
		if(!rdp_send_fonts(This, 1) || !rdp_send_fonts(This, 2))
			return False;
	}

	if(!rdp_recv(This, &type))	/* RDP_PDU_UNKNOWN 0x28 (Fonts?) */
		return False;

	reset_order_state(This);
	return True;
}