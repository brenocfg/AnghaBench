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
typedef  int /*<<< orphan*/  u16_t ;
struct ip_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_3__ {int /*<<< orphan*/  local_port; struct ip_addr local_ip; } ;
typedef  TYPE_1__* PTCP_PCB ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CLSD ; 
 int /*<<< orphan*/  ERR_OK ; 

err_t
LibTCPGetHostName(PTCP_PCB pcb, struct ip_addr *const ipaddr, u16_t *const port)
{
    if (!pcb)
        return ERR_CLSD;

    *ipaddr = pcb->local_ip;
    *port = pcb->local_port;

    return ERR_OK;
}