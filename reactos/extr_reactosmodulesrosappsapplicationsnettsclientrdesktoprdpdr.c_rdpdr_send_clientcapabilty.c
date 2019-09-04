#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8 ;
struct TYPE_6__ {int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {TYPE_1__ rdpdr; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  channel_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  channel_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdpdr_send_clientcapabilty(RDPCLIENT * This)
{
	uint8 magic[4] = "rDPC";
	STREAM s;

	s = channel_init(This, This->rdpdr.channel, 0x50);
	out_uint8a(s, magic, 4);
	out_uint32_le(s, 5);	/* count */
	out_uint16_le(s, 1);	/* first */
	out_uint16_le(s, 0x28);	/* length */
	out_uint32_le(s, 1);
	out_uint32_le(s, 2);
	out_uint16_le(s, 2);
	out_uint16_le(s, 5);
	out_uint16_le(s, 1);
	out_uint16_le(s, 5);
	out_uint16_le(s, 0xFFFF);
	out_uint16_le(s, 0);
	out_uint32_le(s, 0);
	out_uint32_le(s, 3);
	out_uint32_le(s, 0);
	out_uint32_le(s, 0);
	out_uint16_le(s, 2);	/* second */
	out_uint16_le(s, 8);	/* length */
	out_uint32_le(s, 1);
	out_uint16_le(s, 3);	/* third */
	out_uint16_le(s, 8);	/* length */
	out_uint32_le(s, 1);
	out_uint16_le(s, 4);	/* fourth */
	out_uint16_le(s, 8);	/* length */
	out_uint32_le(s, 1);
	out_uint16_le(s, 5);	/* fifth */
	out_uint16_le(s, 8);	/* length */
	out_uint32_le(s, 1);

	s_mark_end(s);
	channel_send(This, s, This->rdpdr.channel);
}