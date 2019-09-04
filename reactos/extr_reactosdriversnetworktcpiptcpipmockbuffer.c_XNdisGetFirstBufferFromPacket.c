#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {struct TYPE_10__* Next; } ;
struct TYPE_8__ {TYPE_3__* Head; } ;
struct TYPE_9__ {TYPE_1__ Private; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__* PUINT ;
typedef  TYPE_2__* PNDIS_PACKET ;
typedef  TYPE_3__* PNDIS_BUFFER ;

/* Variables and functions */
 scalar_t__ MmGetMdlByteCount (TYPE_3__*) ; 
 int /*<<< orphan*/  MmGetMdlVirtualAddress (TYPE_3__*) ; 

VOID XNdisGetFirstBufferFromPacket(PNDIS_PACKET Packet,
				   PNDIS_BUFFER *FirstBuffer,
				   PVOID *FirstBufferVA,
				   PUINT FirstBufferLength,
				   PUINT TotalBufferLength)
{
    PNDIS_BUFFER _Buffer;

    _Buffer              = (Packet)->Private.Head;
    *(FirstBuffer)       = _Buffer;
    *(FirstBufferVA)     = MmGetMdlVirtualAddress(_Buffer);
    if (_Buffer != NULL) {
        *(FirstBufferLength) = MmGetMdlByteCount(_Buffer);
        _Buffer = _Buffer->Next;
    } else
        *(FirstBufferLength) = 0;
    *(TotalBufferLength) = *(FirstBufferLength);
    while (_Buffer != NULL) {
        *(TotalBufferLength) += MmGetMdlByteCount(_Buffer);
        _Buffer = _Buffer->Next;
    }
}