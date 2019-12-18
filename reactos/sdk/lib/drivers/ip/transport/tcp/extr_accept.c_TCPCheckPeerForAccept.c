#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcp_pcb {int dummy; } ;
struct ip_addr {int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int TAAddressCount; TYPE_2__* Address; } ;
struct TYPE_10__ {scalar_t__ RemoteAddress; } ;
struct TYPE_9__ {int RequestFlags; scalar_t__ ReturnConnectionInformation; } ;
struct TYPE_8__ {TYPE_1__* Address; int /*<<< orphan*/  AddressType; int /*<<< orphan*/  AddressLength; } ;
struct TYPE_7__ {int /*<<< orphan*/  in_addr; int /*<<< orphan*/  sin_port; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_3__* PTDI_REQUEST_KERNEL ;
typedef  TYPE_4__* PTDI_CONNECTION_INFORMATION ;
typedef  TYPE_5__* PTA_IP_ADDRESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  LibTCPGetPeerName (struct tcp_pcb*,struct ip_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCPTranslateError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_ADDRESS_LENGTH_IP ; 
 int /*<<< orphan*/  TDI_ADDRESS_TYPE_IP ; 
 int TDI_QUERY_ACCEPT ; 

NTSTATUS TCPCheckPeerForAccept(PVOID Context,
                               PTDI_REQUEST_KERNEL Request)
{
    struct tcp_pcb *newpcb = (struct tcp_pcb*)Context;
    NTSTATUS Status;
    PTDI_CONNECTION_INFORMATION WhoIsConnecting;
    PTA_IP_ADDRESS RemoteAddress;
    struct ip_addr ipaddr;
    
    if (Request->RequestFlags & TDI_QUERY_ACCEPT)
        DbgPrint("TDI_QUERY_ACCEPT NOT SUPPORTED!!!\n");

    WhoIsConnecting = (PTDI_CONNECTION_INFORMATION)Request->ReturnConnectionInformation;
    RemoteAddress = (PTA_IP_ADDRESS)WhoIsConnecting->RemoteAddress;
    
    RemoteAddress->TAAddressCount = 1;
    RemoteAddress->Address[0].AddressLength = TDI_ADDRESS_LENGTH_IP;
    RemoteAddress->Address[0].AddressType = TDI_ADDRESS_TYPE_IP;
    
    Status = TCPTranslateError(LibTCPGetPeerName(newpcb,
                                                 &ipaddr,
                                                 &RemoteAddress->Address[0].Address[0].sin_port));
    
    RemoteAddress->Address[0].Address[0].in_addr = ipaddr.addr;
    
    return Status;
}