#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_20__ {int /*<<< orphan*/ * SocketContext; } ;
struct TYPE_19__ {scalar_t__* OwningModuleInfo; int /*<<< orphan*/  dwState; void* dwRemotePort; int /*<<< orphan*/  dwRemoteAddr; void* dwLocalPort; int /*<<< orphan*/  dwLocalAddr; int /*<<< orphan*/  liCreateTimestamp; int /*<<< orphan*/  dwOwningPid; } ;
struct TYPE_13__ {int /*<<< orphan*/  IPv4Address; } ;
struct TYPE_14__ {TYPE_2__ Address; } ;
struct TYPE_18__ {scalar_t__ SubProcessTag; TYPE_9__* Connection; void* Port; TYPE_3__ Address; TYPE_1__* Listener; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  ProcessId; } ;
struct TYPE_17__ {int TAAddressCount; TYPE_5__* Address; } ;
struct TYPE_16__ {scalar_t__ AddressLength; TYPE_4__* Address; } ;
struct TYPE_15__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  in_addr; } ;
struct TYPE_12__ {TYPE_7__* AddressFile; } ;
typedef  scalar_t__ TDI_TCPUDP_CLASS_INFO ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_6__ TA_IP_ADDRESS ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PTRANSPORT_ADDRESS ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_7__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  MIB_TCPROW_OWNER_PID ;
typedef  TYPE_8__ MIB_TCPROW_OWNER_MODULE ;
typedef  int /*<<< orphan*/  MIB_TCPROW ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HandleToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIB_TCP_STATE_LISTEN ; 
 int NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (scalar_t__*,int) ; 
 int /*<<< orphan*/  TCPGetSockAddress (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPGetSocketStatus (TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TDI_ADDRESS_LENGTH_IP ; 
 int /*<<< orphan*/  TDI_INVALID_REQUEST ; 
 int /*<<< orphan*/  TDI_SUCCESS ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TcpUdpClassOwner ; 
 scalar_t__ TcpUdpClassOwnerPid ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

TDI_STATUS InfoTdiQueryGetConnectionTcpTable(PADDRESS_FILE AddrFile,
				    PNDIS_BUFFER Buffer,
				    PUINT BufferSize,
                    TDI_TCPUDP_CLASS_INFO Class)
{
    SIZE_T Size;
    MIB_TCPROW_OWNER_MODULE TcpRow;
    TDI_STATUS Status = TDI_INVALID_REQUEST;

    TI_DbgPrint(DEBUG_INFO, ("Called.\n"));

    if (Class == TcpUdpClassOwnerPid)
    {
        Size = sizeof(MIB_TCPROW_OWNER_PID);
    }
    else if (Class == TcpUdpClassOwner)
    {
        Size = sizeof(MIB_TCPROW_OWNER_MODULE);
    }
    else
    {
        Size = sizeof(MIB_TCPROW);
    }

    TcpRow.dwOwningPid = HandleToUlong(AddrFile->ProcessId);
    TcpRow.liCreateTimestamp = AddrFile->CreationTime;

    if (AddrFile->Listener != NULL)
    {
        PADDRESS_FILE EndPoint;

        EndPoint = AddrFile->Listener->AddressFile;

        TcpRow.dwState = MIB_TCP_STATE_LISTEN;
        TcpRow.dwLocalAddr = AddrFile->Address.Address.IPv4Address;
        TcpRow.dwLocalPort = AddrFile->Port;
        TcpRow.dwRemoteAddr = EndPoint->Address.Address.IPv4Address;
        TcpRow.dwRemotePort = EndPoint->Port;

        Status = TDI_SUCCESS;
    }
    else if (AddrFile->Connection != NULL &&
             AddrFile->Connection->SocketContext != NULL)
    {
        TA_IP_ADDRESS EndPoint;

        Status = TCPGetSockAddress(AddrFile->Connection, (PTRANSPORT_ADDRESS)&EndPoint, FALSE);
        if (NT_SUCCESS(Status))
        {
            ASSERT(EndPoint.TAAddressCount >= 1);
            ASSERT(EndPoint.Address[0].AddressLength == TDI_ADDRESS_LENGTH_IP);
            TcpRow.dwLocalAddr = EndPoint.Address[0].Address[0].in_addr;
            TcpRow.dwLocalPort = ntohs(EndPoint.Address[0].Address[0].sin_port);

            Status = TCPGetSockAddress(AddrFile->Connection, (PTRANSPORT_ADDRESS)&EndPoint, TRUE);
            if (NT_SUCCESS(Status))
            {
                ASSERT(EndPoint.TAAddressCount >= 1);
                ASSERT(EndPoint.Address[0].AddressLength == TDI_ADDRESS_LENGTH_IP);
                TcpRow.dwRemoteAddr = EndPoint.Address[0].Address[0].in_addr;
                TcpRow.dwRemotePort = ntohs(EndPoint.Address[0].Address[0].sin_port);

                Status = TCPGetSocketStatus(AddrFile->Connection, &TcpRow.dwState);
                ASSERT(NT_SUCCESS(Status));
            }
        }
    }

    if (NT_SUCCESS(Status))
    {
        if (Class == TcpUdpClassOwner)
        {
            RtlZeroMemory(&TcpRow.OwningModuleInfo[0], sizeof(TcpRow.OwningModuleInfo));
            TcpRow.OwningModuleInfo[0] = (ULONG_PTR)AddrFile->SubProcessTag;
        }

        Status = InfoCopyOut( (PCHAR)&TcpRow, Size,
                              Buffer, BufferSize );
    }

    TI_DbgPrint(DEBUG_INFO, ("Returning %08x\n", Status));

    return Status;
}