#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8 ;
typedef  int uint32 ;
struct TYPE_7__ {int /*<<< orphan*/  channel; } ;
struct TYPE_8__ {TYPE_1__ rdpdr; int /*<<< orphan*/ * rdpdr_clientname; int /*<<< orphan*/ * hostname; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  channel_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  channel_send (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rdpdr_send_name(RDPCLIENT * This)
{
	uint8 magic[4] = "rDNC";
	STREAM s;
	uint32 hostlen;

	if (NULL == This->rdpdr_clientname)
	{
		This->rdpdr_clientname = This->hostname;
	}
	hostlen = (strlen(This->rdpdr_clientname) + 1) * 2;

	s = channel_init(This, This->rdpdr.channel, 16 + hostlen);
	out_uint8a(s, magic, 4);
	out_uint16_le(s, 0x63);	/* unknown */
	out_uint16_le(s, 0x72);
	out_uint32(s, 0);
	out_uint32_le(s, hostlen);
	rdp_out_unistr(This, s, This->rdpdr_clientname, hostlen - 2);
	s_mark_end(s);
	channel_send(This, s, This->rdpdr.channel);
}