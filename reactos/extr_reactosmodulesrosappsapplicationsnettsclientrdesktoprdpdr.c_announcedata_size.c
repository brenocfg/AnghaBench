#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bloblen; int /*<<< orphan*/  printer; int /*<<< orphan*/  driver; int /*<<< orphan*/  blob; } ;
struct TYPE_6__ {int num_devices; TYPE_1__* rdpdr_device; } ;
struct TYPE_5__ {scalar_t__ device_type; scalar_t__ pdevice_data; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  TYPE_3__ PRINTER ;

/* Variables and functions */
 scalar_t__ DEVICE_TYPE_PRINTER ; 
 scalar_t__ printercache_load_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
announcedata_size(RDPCLIENT * This)
{
	int size, i;
	PRINTER *printerinfo;

	size = 8;		/* static announce size */
	size += This->num_devices * 0x14;

	for (i = 0; i < This->num_devices; i++)
	{
		if (This->rdpdr_device[i].device_type == DEVICE_TYPE_PRINTER)
		{
			printerinfo = (PRINTER *) This->rdpdr_device[i].pdevice_data;
			printerinfo->bloblen =
				printercache_load_blob(printerinfo->printer, &(printerinfo->blob));

			size += 0x18;
			size += 2 * strlen(printerinfo->driver) + 2;
			size += 2 * strlen(printerinfo->printer) + 2;
			size += printerinfo->bloblen;
		}
	}

	return size;
}