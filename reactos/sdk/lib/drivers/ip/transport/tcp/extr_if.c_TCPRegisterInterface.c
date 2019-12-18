#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip_addr {scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  TCPContext; } ;
typedef  TYPE_1__* PIP_INTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  TCPInterfaceInit ; 
 int /*<<< orphan*/  netif_add (int /*<<< orphan*/ ,struct ip_addr*,struct ip_addr*,struct ip_addr*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpip_input ; 

VOID
TCPRegisterInterface(PIP_INTERFACE IF)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;
    
    gw.addr = 0;
    ipaddr.addr = 0;
    netmask.addr = 0;
    
    IF->TCPContext = netif_add(IF->TCPContext, 
                               &ipaddr,
                               &netmask,
                               &gw,
                               IF,
                               TCPInterfaceInit,
                               tcpip_input);
}