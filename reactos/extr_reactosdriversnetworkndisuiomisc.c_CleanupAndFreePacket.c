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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreeBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisFreePacket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdisQueryBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NdisUnchainBufferAtFront (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

VOID
CleanupAndFreePacket(PNDIS_PACKET Packet, BOOLEAN FreePool)
{
    PNDIS_BUFFER Buffer;
    PVOID Data;
    ULONG Length;

    /* Free each buffer and its backing pool memory */
    while (TRUE)
    {
        /* Unchain each buffer */
        NdisUnchainBufferAtFront(Packet, &Buffer);
        if (!Buffer)
            break;
        
        /* Get the backing memory */
        NdisQueryBuffer(Buffer, &Data, &Length);
        
        /* Free the buffer */
        NdisFreeBuffer(Buffer);

        if (FreePool)
        {
            /* Free the backing memory */
            ExFreePool(Data);
        }
    }
    
    /* Free the packet descriptor */
    NdisFreePacket(Packet);
}