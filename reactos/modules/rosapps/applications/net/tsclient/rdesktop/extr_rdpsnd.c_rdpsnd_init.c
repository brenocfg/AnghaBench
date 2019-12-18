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
struct TYPE_6__ {TYPE_1__ rdpsnd; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CHANNEL_OPTION_ENCRYPT_RDP ; 
 int CHANNEL_OPTION_INITIALIZED ; 
 int /*<<< orphan*/ * channel_register (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpsnd_process ; 

BOOL
rdpsnd_init(RDPCLIENT * This)
{
	This->rdpsnd.channel =
		channel_register(This, "rdpsnd", CHANNEL_OPTION_INITIALIZED | CHANNEL_OPTION_ENCRYPT_RDP,
				 rdpsnd_process);
	return (This->rdpsnd.channel != NULL);
}