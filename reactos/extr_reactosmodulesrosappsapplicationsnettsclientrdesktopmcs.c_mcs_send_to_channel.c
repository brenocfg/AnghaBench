#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
struct TYPE_11__ {int mcs_userid; } ;
struct TYPE_10__ {int end; int p; } ;
typedef  TYPE_1__* STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int MCS_SDRQ ; 
 int /*<<< orphan*/  iso_send (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mcs_hdr ; 
 int /*<<< orphan*/  out_uint16_be (TYPE_1__*,int) ; 
 int /*<<< orphan*/  out_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_pop_layer (TYPE_1__*,int /*<<< orphan*/ ) ; 

BOOL
mcs_send_to_channel(RDPCLIENT * This, STREAM s, uint16 channel)
{
	uint16 length;

	s_pop_layer(s, mcs_hdr);
	length = (uint16)(s->end - s->p - 8);
	length |= 0x8000;

	out_uint8(s, (MCS_SDRQ << 2));
	out_uint16_be(s, This->mcs_userid);
	out_uint16_be(s, channel);
	out_uint8(s, 0x70);	/* flags */
	out_uint16_be(s, length);

	return iso_send(This, s);
}