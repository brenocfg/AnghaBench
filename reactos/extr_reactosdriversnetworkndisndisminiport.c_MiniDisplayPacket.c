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
typedef  int /*<<< orphan*/  PNDIS_PACKET ;
typedef  int /*<<< orphan*/  PCSTR ;

/* Variables and functions */

VOID
MiniDisplayPacket(
    PNDIS_PACKET Packet,
    PCSTR Reason)
{
#if DBG
    ULONG i, Length;
    UCHAR Buffer[64];
    if ((DebugTraceLevel & DEBUG_PACKET) > 0) {
        Length = CopyPacketToBuffer(
            Buffer,
            Packet,
            0,
            64);

        DbgPrint("*** %s PACKET START (%p) ***\n", Reason, Packet);

        for (i = 0; i < Length; i++) {
            if (i % 16 == 0)
                DbgPrint("\n%04X ", i);
            DbgPrint("%02X ", Buffer[i]);
        }

        DbgPrint("\n*** %s PACKET STOP ***\n", Reason);
    }
#endif /* DBG */
}