#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_7__ {scalar_t__ p; scalar_t__ end; } ;
typedef  TYPE_1__* STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ISO_PDU_DT ; 
 int /*<<< orphan*/  iso_hdr ; 
 int /*<<< orphan*/  out_uint16_be (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  s_pop_layer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_send (int /*<<< orphan*/ *,TYPE_1__*) ; 

BOOL
iso_send(RDPCLIENT * This, STREAM s)
{
	uint16 length;

	s_pop_layer(s, iso_hdr);
	length = (uint16)(s->end - s->p);

	out_uint8(s, 3);	/* version */
	out_uint8(s, 0);	/* reserved */
	out_uint16_be(s, length);

	out_uint8(s, 2);	/* hdrlen */
	out_uint8(s, ISO_PDU_DT);	/* code */
	out_uint8(s, 0x80);	/* eot */

	return tcp_send(This, s);
}