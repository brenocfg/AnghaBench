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
struct TYPE_5__ {int /*<<< orphan*/ * channel; scalar_t__ serial; } ;
struct TYPE_6__ {TYPE_1__ seamless; int /*<<< orphan*/  seamless_rdp; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CHANNEL_OPTION_ENCRYPT_RDP ; 
 int CHANNEL_OPTION_INITIALIZED ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/ * channel_register (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seamless_process ; 

BOOL
seamless_init(RDPCLIENT * This)
{
	if (!This->seamless_rdp)
		return False;

	This->seamless.serial = 0;

	This->seamless.channel =
		channel_register(This, "seamrdp", CHANNEL_OPTION_INITIALIZED | CHANNEL_OPTION_ENCRYPT_RDP,
				 seamless_process);
	return (This->seamless.channel != NULL);
}