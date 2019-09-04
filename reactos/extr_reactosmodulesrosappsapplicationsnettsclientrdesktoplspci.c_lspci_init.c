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
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CHANNEL_OPTION_ENCRYPT_RDP ; 
 int CHANNEL_OPTION_INITIALIZED ; 
 int /*<<< orphan*/ * channel_register (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lspci_channel ; 
 int /*<<< orphan*/  lspci_process ; 

BOOL
lspci_init(RDPCLIENT * This)
{
	lspci_channel =
		channel_register(This, "lspci", CHANNEL_OPTION_INITIALIZED | CHANNEL_OPTION_ENCRYPT_RDP,
				 lspci_process);
	return (lspci_channel != NULL);
}