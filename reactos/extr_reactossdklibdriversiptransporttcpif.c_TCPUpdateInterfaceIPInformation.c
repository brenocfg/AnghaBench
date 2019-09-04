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
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_1__* PIP_INTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  ADE_ADDRMASK ; 
 int /*<<< orphan*/  ADE_UNICAST ; 
 int /*<<< orphan*/  GetInterfaceIPv4Address (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_addr (int /*<<< orphan*/ ,struct ip_addr*,struct ip_addr*,struct ip_addr*) ; 
 int /*<<< orphan*/  netif_set_default (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_up (int /*<<< orphan*/ ) ; 

VOID
TCPUpdateInterfaceIPInformation(PIP_INTERFACE IF)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;
    
    gw.addr = 0;
    
    GetInterfaceIPv4Address(IF,
                            ADE_UNICAST,
                            (PULONG)&ipaddr.addr);
    
    GetInterfaceIPv4Address(IF,
                            ADE_ADDRMASK,
                            (PULONG)&netmask.addr);
    
    netif_set_addr(IF->TCPContext, &ipaddr, &netmask, &gw);
    
    if (ipaddr.addr != 0)
    {
        netif_set_up(IF->TCPContext);
        netif_set_default(IF->TCPContext);
    }
    else
    {
        netif_set_down(IF->TCPContext);
    }
}