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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  RDPSND_COMPLETION ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpsnd_init_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdpsnd_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

void
rdpsnd_send_completion(RDPCLIENT * This, uint16 tick, uint8 packet_index)
{
	STREAM s;

	s = rdpsnd_init_packet(This, RDPSND_COMPLETION, 4);
	out_uint16_le(s, tick + 50);
	out_uint8(s, packet_index);
	out_uint8(s, 0);
	s_mark_end(s);
	rdpsnd_send(This, s);
}