#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ ULONG_PTR ;
typedef  int UINT ;
struct TYPE_6__ {int BytesLeft; int PathMTU; int HeaderSize; int Position; scalar_t__ DatagramData; TYPE_1__* Header; int /*<<< orphan*/  Data; } ;
struct TYPE_5__ {scalar_t__ Checksum; void* TotalLength; void* FlagsFragOfs; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PIPv4_HEADER ;
typedef  TYPE_2__* PIPFRAGMENT_CONTEXT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IPv4Checksum (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IPv4_MF_MASK ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TRUE ; 
 void* WH2N (scalar_t__) ; 

BOOLEAN PrepareNextFragment(
    PIPFRAGMENT_CONTEXT IFC)
/*
 * FUNCTION: Prepares the next fragment of an IP datagram for transmission
 * ARGUMENTS:
 *     IFC = Pointer to IP fragment context
 * RETURNS:
 *     TRUE if a fragment was prepared for transmission, FALSE if
 *     there are no more fragments to send
 */
{
    UINT MaxData;
    UINT DataSize;
    PIPv4_HEADER Header;
    BOOLEAN MoreFragments;
    USHORT FragOfs;

    TI_DbgPrint(MAX_TRACE, ("Called. IFC (0x%X)\n", IFC));

    if (IFC->BytesLeft > 0) {

        TI_DbgPrint(MAX_TRACE, ("Preparing 1 fragment.\n"));

        MaxData  = IFC->PathMTU - IFC->HeaderSize;
        /* Make fragment a multiplum of 64bit */
        MaxData -= MaxData % 8;
        if (IFC->BytesLeft > MaxData) {
            DataSize      = MaxData;
            MoreFragments = TRUE;
        } else {
            DataSize      = IFC->BytesLeft;
            MoreFragments = FALSE;
        }

	TI_DbgPrint(MID_TRACE,("Copying data from %x to %x (%d)\n",
			       IFC->DatagramData, IFC->Data, DataSize));

        RtlCopyMemory(IFC->Data, IFC->DatagramData, DataSize); // SAFE

        /* Fragment offset is in 8 byte blocks */
        FragOfs = (USHORT)(IFC->Position / 8);

        if (MoreFragments)
            FragOfs |= IPv4_MF_MASK;
        else
            FragOfs &= ~IPv4_MF_MASK;

        Header = IFC->Header;
        Header->FlagsFragOfs = WH2N(FragOfs);
        Header->TotalLength = WH2N((USHORT)(DataSize + IFC->HeaderSize));

        /* FIXME: Handle options */

        /* Calculate checksum of IP header */
        Header->Checksum = 0;
        Header->Checksum = (USHORT)IPv4Checksum(Header, IFC->HeaderSize, 0);
	TI_DbgPrint(MID_TRACE,("IP Check: %x\n", Header->Checksum));

        /* Update pointers */
        IFC->DatagramData = (PVOID)((ULONG_PTR)IFC->DatagramData + DataSize);
        IFC->Position  += DataSize;
        IFC->BytesLeft -= DataSize;

        return TRUE;
    } else {
        TI_DbgPrint(MAX_TRACE, ("No more fragments.\n"));
        return FALSE;
    }
}