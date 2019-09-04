#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_13__ {scalar_t__ next_packet; } ;
struct TYPE_12__ {scalar_t__ end; } ;
typedef  TYPE_1__* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int False ; 
#define  RDP_PDU_DATA 131 
#define  RDP_PDU_DEACTIVATE 130 
#define  RDP_PDU_DEMAND_ACTIVE 129 
#define  RDP_PDU_REDIRECT 128 
 int True ; 
 int process_data_pdu (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_demand_active (TYPE_2__*,TYPE_1__*) ; 
 int process_redirect_pdu (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* rdp_recv (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

BOOL
rdp_loop(RDPCLIENT * This, BOOL * deactivated, uint32 * ext_disc_reason)
{
	uint8 type;
	BOOL disc = False;	/* True when a disconnect PDU was received */
	BOOL cont = True;
	STREAM s;

	while (cont)
	{
		s = rdp_recv(This, &type);
		if (s == NULL)
			return False;
		switch (type)
		{
			case RDP_PDU_DEMAND_ACTIVE:
				if(!process_demand_active(This, s))
					return False;
				*deactivated = False;
				break;
			case RDP_PDU_DEACTIVATE:
				DEBUG(("RDP_PDU_DEACTIVATE\n"));
				*deactivated = True;
				break;
			case RDP_PDU_REDIRECT:
				return process_redirect_pdu(This, s);
				break;
			case RDP_PDU_DATA:
				disc = process_data_pdu(This, s, ext_disc_reason);
				break;
			case 0:
				break;
			default:
				unimpl("PDU %d\n", type);
		}
		if (disc)
			return False;
		cont = This->next_packet < s->end;
	}
	return True;
}