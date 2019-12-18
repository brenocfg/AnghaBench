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
typedef  int uint16 ;
struct TYPE_13__ {int mcs_userid; scalar_t__ encryption; int /*<<< orphan*/  rdp_shareid; } ;
struct TYPE_12__ {scalar_t__ p; scalar_t__ end; } ;
typedef  TYPE_1__* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int RDP_PDU_DATA ; 
 int /*<<< orphan*/  SEC_ENCRYPT ; 
 int /*<<< orphan*/  out_uint16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  out_uint32_le (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rdp_hdr ; 
 int /*<<< orphan*/  s_pop_layer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_send (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
rdp_send_data(RDPCLIENT * This, STREAM s, uint8 data_pdu_type)
{
	uint16 length;

	s_pop_layer(s, rdp_hdr);
	length = (uint16)(s->end - s->p);

	out_uint16_le(s, length);
	out_uint16_le(s, (RDP_PDU_DATA | 0x10));
	out_uint16_le(s, (This->mcs_userid + 1001));

	out_uint32_le(s, This->rdp_shareid);
	out_uint8(s, 0);	/* pad */
	out_uint8(s, 1);	/* streamid */
	out_uint16_le(s, (length - 14));
	out_uint8(s, data_pdu_type);
	out_uint8(s, 0);	/* compress_type */
	out_uint16(s, 0);	/* compress_len */

	return sec_send(This, s, This->encryption ? SEC_ENCRYPT : 0);
}