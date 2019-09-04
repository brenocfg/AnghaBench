#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int uint16 ;
struct stream {int* p; int* data; int size; int* end; int* rdp_hdr; } ;
struct TYPE_9__ {scalar_t__ hist; struct stream ns; } ;
struct TYPE_10__ {int disconnect_reason; TYPE_1__ mppc_dict; } ;
typedef  struct stream* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  False ; 
#define  RDP_DATA_PDU_BELL 134 
#define  RDP_DATA_PDU_CONTROL 133 
#define  RDP_DATA_PDU_DISCONNECT 132 
#define  RDP_DATA_PDU_LOGON 131 
#define  RDP_DATA_PDU_POINTER 130 
#define  RDP_DATA_PDU_SYNCHRONISE 129 
#define  RDP_DATA_PDU_UPDATE 128 
 int RDP_MPPC_COMPRESSED ; 
 scalar_t__ RDP_MPPC_DICT_SIZE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  event_logon (TYPE_2__*) ; 
 int /*<<< orphan*/  in_uint16 (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8 (struct stream*,int) ; 
 int /*<<< orphan*/  in_uint8s (struct stream*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char*,scalar_t__) ; 
 int mppc_expand (TYPE_2__*,int*,int,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  process_disconnect_pdu (struct stream*,scalar_t__*) ; 
 int /*<<< orphan*/  process_pointer_pdu (TYPE_2__*,struct stream*) ; 
 int /*<<< orphan*/  process_update_pdu (TYPE_2__*,struct stream*) ; 
 void* realloc (int*,scalar_t__) ; 
 int /*<<< orphan*/  ui_bell (TYPE_2__*) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

__attribute__((used)) static BOOL
process_data_pdu(RDPCLIENT * This, STREAM s, uint32 * ext_disc_reason)
{
	uint8 data_pdu_type;
	uint8 ctype;
	uint16 clen;
	uint32 len;

	uint32 roff, rlen;

	struct stream *ns = &(This->mppc_dict.ns);

	in_uint8s(s, 6);	/* shareid, pad, streamid */
	in_uint16(s, len);
	in_uint8(s, data_pdu_type);
	in_uint8(s, ctype);
	in_uint16(s, clen);
	clen -= 18;

	if (ctype & RDP_MPPC_COMPRESSED)
	{
		void * p;

		if (len > RDP_MPPC_DICT_SIZE)
			error("error decompressed packet size exceeds max\n");
		if (mppc_expand(This, s->p, clen, ctype, &roff, &rlen) == -1)
			error("error while decompressing packet\n");

		/* len -= 18; */

		/* allocate memory and copy the uncompressed data into the temporary stream */
		p = realloc(ns->data, rlen);

		if(p == NULL)
		{
			This->disconnect_reason = 262;
			return True;
		}

		ns->data = (uint8 *) p;

		memcpy((ns->data), (unsigned char *) (This->mppc_dict.hist + roff), rlen);

		ns->size = rlen;
		ns->end = (ns->data + ns->size);
		ns->p = ns->data;
		ns->rdp_hdr = ns->p;

		s = ns;
	}

	switch (data_pdu_type)
	{
		case RDP_DATA_PDU_UPDATE:
			process_update_pdu(This, s);
			break;

		case RDP_DATA_PDU_CONTROL:
			DEBUG(("Received Control PDU\n"));
			break;

		case RDP_DATA_PDU_SYNCHRONISE:
			DEBUG(("Received Sync PDU\n"));
			break;

		case RDP_DATA_PDU_POINTER:
			process_pointer_pdu(This, s);
			break;

		case RDP_DATA_PDU_BELL:
			ui_bell(This);
			break;

		case RDP_DATA_PDU_LOGON:
			DEBUG(("Received Logon PDU\n"));
			event_logon(This);
			/* User logged on */
			break;

		case RDP_DATA_PDU_DISCONNECT:
			process_disconnect_pdu(s, ext_disc_reason);

			/* We used to return true and disconnect immediately here, but
			 * Windows Vista sends a disconnect PDU with reason 0 when
			 * reconnecting to a disconnected session, and MSTSC doesn't
			 * drop the connection.  I think we should just save the status.
			 */
			break;

		default:
			unimpl("data PDU %d\n", data_pdu_type);
	}
	return False;
}