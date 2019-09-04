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
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ toi_type; int toi_id; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_1__ TDIObjectID ;
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PCONNECTION_ENDPOINT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DbgPrint (char*,int) ; 
 scalar_t__ INFO_TYPE_CONNECTION ; 
 int /*<<< orphan*/  TCPSetNoDelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TCP_SOCKET_NODELAY 128 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 

TDI_STATUS SetConnectionInfo(TDIObjectID *ID,
                             PCONNECTION_ENDPOINT Connection,
                             PVOID Buffer,
                             UINT BufferSize)
{
    ASSERT(ID->toi_type == INFO_TYPE_CONNECTION);
    switch (ID->toi_id)
    {
        case TCP_SOCKET_NODELAY:
        {
            BOOLEAN Set;
            if (BufferSize < sizeof(BOOLEAN))
                return TDI_INVALID_PARAMETER;
            Set = *(BOOLEAN*)Buffer;
            return TCPSetNoDelay(Connection, Set);
        }
        default:
            DbgPrint("TCPIP: Unknown connection info ID: %u.\n", ID->toi_id);
    }

    return TDI_INVALID_PARAMETER;
}