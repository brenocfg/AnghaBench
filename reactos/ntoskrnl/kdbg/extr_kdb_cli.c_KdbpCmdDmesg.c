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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KdbDmesgTotalWritten ; 
 int /*<<< orphan*/  KdbpIsInDmesgMode ; 
 int /*<<< orphan*/  KdbpPager (scalar_t__,int) ; 
 int /*<<< orphan*/  KdbpPrint (char*,...) ; 
 scalar_t__ KdpDmesgBuffer ; 
 int KdpDmesgBufferSize ; 
 int KdpDmesgCurrentPosition ; 
 int KdpDmesgFreeBytes ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
KdbpCmdDmesg(
    ULONG Argc,
    PCHAR Argv[])
{
    ULONG beg, end;

    KdbpIsInDmesgMode = TRUE; /* Toggle logging flag */
    if (!KdpDmesgBuffer)
    {
        KdbpPrint("Dmesg: error, buffer is not allocated! /DEBUGPORT=SCREEN kernel param required for dmesg.\n");
        return TRUE;
    }

    KdbpPrint("*** Dmesg *** TotalWritten=%lu, BufferSize=%lu, CurrentPosition=%lu\n",
              KdbDmesgTotalWritten, KdpDmesgBufferSize, KdpDmesgCurrentPosition);

    /* Pass data to the pager */
    end = KdpDmesgCurrentPosition;
    beg = (end + KdpDmesgFreeBytes) % KdpDmesgBufferSize;

    /* No roll-overs, and overwritten=lost bytes */
    if (KdbDmesgTotalWritten <= KdpDmesgBufferSize)
    {
        /* Show buffer (KdpDmesgBuffer + beg, num) */
        KdbpPager(KdpDmesgBuffer, KdpDmesgCurrentPosition);
    }
    else
    {
        /* Show 2 buffers: (KdpDmesgBuffer + beg, KdpDmesgBufferSize - beg)
         *            and: (KdpDmesgBuffer,       end) */
        KdbpPager(KdpDmesgBuffer + beg, KdpDmesgBufferSize - beg);
        KdbpPrint("*** Dmesg: buffer rollup ***\n");
        KdbpPager(KdpDmesgBuffer,       end);
    }
    KdbpPrint("*** Dmesg: end of output ***\n");

    KdbpIsInDmesgMode = FALSE; /* Toggle logging flag */

    return TRUE;
}