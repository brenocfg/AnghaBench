#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
struct TYPE_12__ {int /*<<< orphan*/  packetno; } ;
struct TYPE_14__ {int /*<<< orphan*/ * next_packet; TYPE_1__ rdp; } ;
struct TYPE_13__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * end; } ;
typedef  TYPE_2__* STREAM ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  hexdump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint16_le (TYPE_2__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rdp5_process (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* sec_recv (TYPE_3__*,int*) ; 

__attribute__((used)) static STREAM
rdp_recv(RDPCLIENT * This, uint8 * type)
{
	static STREAM rdp_s; // FIXME HORROR
	uint16 length, pdu_type;
	uint8 rdpver;

	if ((rdp_s == NULL) || (This->next_packet >= rdp_s->end) || (This->next_packet == NULL))
	{
		rdp_s = sec_recv(This, &rdpver);
		if (rdp_s == NULL)
			return NULL;
		if (rdpver == 0xff)
		{
			This->next_packet = rdp_s->end;
			*type = 0;
			return rdp_s;
		}
		else if (rdpver != 3)
		{
			/* rdp5_process should move This->next_packet ok */
			if(!rdp5_process(This, rdp_s))
				return NULL;
			*type = 0;
			return rdp_s;
		}

		This->next_packet = rdp_s->p;
	}
	else
	{
		rdp_s->p = This->next_packet;
	}

	in_uint16_le(rdp_s, length);
	/* 32k packets are really 8, keepalive fix */
	if (length == 0x8000)
	{
		This->next_packet += 8;
		*type = 0;
		return rdp_s;
	}
	in_uint16_le(rdp_s, pdu_type);
	in_uint8s(rdp_s, 2);	/* userid */
	*type = pdu_type & 0xf;

#if WITH_DEBUG
	DEBUG(("RDP packet #%d, (type %x)\n", ++This->rdp.packetno, *type));
	hexdump(This->next_packet, length);
#endif /*  */

	This->next_packet += length;
	return rdp_s;
}