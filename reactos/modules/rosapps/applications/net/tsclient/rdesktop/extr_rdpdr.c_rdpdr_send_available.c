#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8 ;
typedef  int uint32 ;
struct TYPE_13__ {int bloblen; char* blob; int /*<<< orphan*/  printer; int /*<<< orphan*/  driver; int /*<<< orphan*/  default_printer; } ;
struct TYPE_11__ {int /*<<< orphan*/  channel; } ;
struct TYPE_12__ {int num_devices; TYPE_2__ rdpdr; TYPE_1__* rdpdr_device; } ;
struct TYPE_10__ {int device_type; char* name; scalar_t__ pdevice_data; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_3__ RDPCLIENT ;
typedef  TYPE_4__ PRINTER ;

/* Variables and functions */
#define  DEVICE_TYPE_PRINTER 128 
 int /*<<< orphan*/  announcedata_size (TYPE_3__*) ; 
 int /*<<< orphan*/  channel_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel_send (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint32_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_uint8a (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  out_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdp_out_unistr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
rdpdr_send_available(RDPCLIENT * This)
{

	uint8 magic[4] = "rDAD";
	uint32 driverlen, printerlen, bloblen;
	int i;
	STREAM s;
	PRINTER *printerinfo;

	s = channel_init(This, This->rdpdr.channel, announcedata_size(This));
	out_uint8a(s, magic, 4);
	out_uint32_le(s, This->num_devices);

	for (i = 0; i < This->num_devices; i++)
	{
		out_uint32_le(s, This->rdpdr_device[i].device_type);
		out_uint32_le(s, i);	/* RDP Device ID */
		/* Is it possible to use share names longer than 8 chars?
		   /astrand */
		out_uint8p(s, This->rdpdr_device[i].name, 8);

		switch (This->rdpdr_device[i].device_type)
		{
			case DEVICE_TYPE_PRINTER:
				printerinfo = (PRINTER *) This->rdpdr_device[i].pdevice_data;

				driverlen = 2 * strlen(printerinfo->driver) + 2;
				printerlen = 2 * strlen(printerinfo->printer) + 2;
				bloblen = printerinfo->bloblen;

				out_uint32_le(s, 24 + driverlen + printerlen + bloblen);	/* length of extra info */
				out_uint32_le(s, printerinfo->default_printer ? 2 : 0);
				out_uint8s(s, 8);	/* unknown */
				out_uint32_le(s, driverlen);
				out_uint32_le(s, printerlen);
				out_uint32_le(s, bloblen);
				rdp_out_unistr(This, s, printerinfo->driver, driverlen - 2);
				rdp_out_unistr(This, s, printerinfo->printer, printerlen - 2);
				out_uint8a(s, printerinfo->blob, bloblen);

				if (printerinfo->blob)
					xfree(printerinfo->blob);	/* Blob is sent twice if reconnecting */
				break;
			default:
				out_uint32(s, 0);
		}
	}
#if 0
	out_uint32_le(s, 0x20);	/* Device type 0x20 - smart card */
	out_uint32_le(s, 0);
	out_uint8p(s, "SCARD", 5);
	out_uint8s(s, 3);
	out_uint32(s, 0);
#endif

	s_mark_end(s);
	channel_send(This, s, This->rdpdr.channel);
}