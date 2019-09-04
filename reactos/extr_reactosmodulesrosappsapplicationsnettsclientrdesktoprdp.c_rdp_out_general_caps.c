#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ use_rdp5; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int RDP_CAPLEN_GENERAL ; 
 int RDP_CAPSET_GENERAL ; 
 int /*<<< orphan*/  out_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_out_general_caps(RDPCLIENT * This, STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_GENERAL);
	out_uint16_le(s, RDP_CAPLEN_GENERAL);

	out_uint16_le(s, 1);	/* OS major type */
	out_uint16_le(s, 3);	/* OS minor type */
	out_uint16_le(s, 0x200);	/* Protocol version */
	out_uint16(s, 0);	/* Pad */
	out_uint16(s, 0);	/* Compression types */
	out_uint16_le(s, This->use_rdp5 ? 0x40d : 0);
	/* Pad, according to T.128. 0x40d seems to
	   trigger
	   the server to start sending RDP5 packets.
	   However, the value is 0x1d04 with W2KTSK and
	   NT4MS. Hmm.. Anyway, thankyou, Microsoft,
	   for sending such information in a padding
	   field.. */
	out_uint16(s, 0);	/* Update capability */
	out_uint16(s, 0);	/* Remote unshare capability */
	out_uint16(s, 0);	/* Compression level */
	out_uint16(s, 0);	/* Pad */
}