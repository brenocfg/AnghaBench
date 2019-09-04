#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
typedef  int ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  SizeOfHeaders; TYPE_1__* DataDirectory; int /*<<< orphan*/  NumberOfRvaAndSizes; } ;
struct TYPE_8__ {TYPE_2__ OptionalHeader; } ;
struct TYPE_6__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  VirtualAddress; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_3__* PIMAGE_NT_HEADERS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_3__* RtlImageNtHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RtlImageRvaToVa (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SWAPD (int /*<<< orphan*/ ) ; 

PVOID
__RtlImageDirectoryEntryToData(
    PVOID BaseAddress,
    BOOLEAN MappedAsImage,
    USHORT Directory,
    PULONG Size)
{
    PIMAGE_NT_HEADERS NtHeader;
    ULONG Va;

    /* Magic flag for non-mapped images. */
    if ((ULONG_PTR)BaseAddress & 1)
    {
        BaseAddress = (PVOID)((ULONG_PTR)BaseAddress & ~1);
        MappedAsImage = FALSE;
    }

    NtHeader = RtlImageNtHeader(BaseAddress);
    if (NtHeader == NULL)
        return NULL;

    if (Directory >= SWAPD(NtHeader->OptionalHeader.NumberOfRvaAndSizes))
        return NULL;

    Va = SWAPD(NtHeader->OptionalHeader.DataDirectory[Directory].VirtualAddress);
    if (Va == 0)
        return NULL;

    *Size = SWAPD(NtHeader->OptionalHeader.DataDirectory[Directory].Size);

    if (MappedAsImage || Va < SWAPD(NtHeader->OptionalHeader.SizeOfHeaders))
        return (PVOID)((ULONG_PTR)BaseAddress + Va);

    /* Image mapped as ordinary file, we must find raw pointer */
    return RtlImageRvaToVa(NtHeader, BaseAddress, Va, NULL);
}