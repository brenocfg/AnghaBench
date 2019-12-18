#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * channel; } ;
struct TYPE_6__ {scalar_t__ num_devices; TYPE_1__ rdpdr; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CHANNEL_OPTION_COMPRESS_RDP ; 
 int CHANNEL_OPTION_INITIALIZED ; 
 int /*<<< orphan*/ * channel_register (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpdr_process ; 

BOOL
rdpdr_init(RDPCLIENT * This)
{
	if (This->num_devices > 0)
	{
		This->rdpdr.channel =
			channel_register(This, "rdpdr",
					 CHANNEL_OPTION_INITIALIZED | CHANNEL_OPTION_COMPRESS_RDP,
					 rdpdr_process);
	}

	return (This->rdpdr.channel != NULL);
}