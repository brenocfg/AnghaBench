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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
 int RDPSND_SERVERTICK ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpsnd_init_packet (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rdpsnd_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdpsnd_process_servertick(RDPCLIENT * This, STREAM in)
{
	uint16 tick1, tick2;
	STREAM out;

	/* in_uint8s(in, 4); unknown */
	in_uint16_le(in, tick1);
	in_uint16_le(in, tick2);

	out = rdpsnd_init_packet(This, RDPSND_SERVERTICK | 0x2300, 4);
	out_uint16_le(out, tick1);
	out_uint16_le(out, tick2);
	s_mark_end(out);
	rdpsnd_send(This, out);
}