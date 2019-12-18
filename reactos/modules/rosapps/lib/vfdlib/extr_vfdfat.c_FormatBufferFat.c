#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
typedef  int ULONG ;
struct TYPE_12__ {int ReservedSectors; int SectorsPerFAT; int NumberOfFATs; int MediaDescriptor; int RootEntries; } ;
struct TYPE_10__ {int BootSignature; int /*<<< orphan*/ * FileSystemType; int /*<<< orphan*/ * VolumeLabel; int /*<<< orphan*/  VolumeSerialNumber; } ;
struct TYPE_11__ {TYPE_1__ exbpb; int /*<<< orphan*/  bpb; int /*<<< orphan*/ * oemid; int /*<<< orphan*/ * jump; } ;
typedef  int* PUCHAR ;
typedef  TYPE_2__* PDOS_PBR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ DOS_BPB ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,TYPE_3__ const*,int) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int FAT_DIR_ENTRY_SIZE ; 
 int /*<<< orphan*/  FillMemory (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTickCount () ; 
 TYPE_3__* SelectDosBpb (int) ; 
 int /*<<< orphan*/  VFDTRACE (int /*<<< orphan*/ ,char*) ; 
 int VFD_BYTES_PER_SECTOR ; 
 TYPE_3__ const* VFD_FILESYSTEM ; 
 int /*<<< orphan*/  VFD_FORMAT_FILL_DATA ; 
 TYPE_3__ const* VFD_JUMP_CODE ; 
 TYPE_3__ const* VFD_OEM_NAME ; 
 int VFD_SECTOR_TO_BYTE (int) ; 
 TYPE_3__ const* VFD_VOLUME_LABEL ; 
 int /*<<< orphan*/  ZeroMemory (int*,int) ; 

DWORD FormatBufferFat(
	PUCHAR			pBuffer,
	ULONG			nSectors)
{
	const DOS_BPB	*bpb;	// BIOS Parameter Block
	PDOS_PBR		pbr;	// Partition Boot Record
	PUCHAR			fat;	// File Allocation Table
	USHORT			idx;

	VFDTRACE(0,
		("[VFD] VfdFormatImage - IN\n"));

	//
	//	Select DOS BPB parameters from media size
	//
	bpb = SelectDosBpb((USHORT)nSectors);

	if (!bpb) {
		VFDTRACE(0,
			("[VFD] Unsupported media size %lu\n",
			nSectors));
		return ERROR_INVALID_PARAMETER;
	}

	//
	//	Initialize the whole area with the fill data
	//
	FillMemory(pBuffer,
		VFD_SECTOR_TO_BYTE(nSectors),
		VFD_FORMAT_FILL_DATA);

	//
	//	Make up the FAT boot record
	//
	ZeroMemory(pBuffer, VFD_BYTES_PER_SECTOR);

	pbr = (PDOS_PBR)pBuffer;

	CopyMemory(pbr->jump,	VFD_JUMP_CODE,	sizeof(pbr->jump));
	CopyMemory(pbr->oemid,	VFD_OEM_NAME,	sizeof(pbr->oemid));
	CopyMemory(&pbr->bpb,	bpb,			sizeof(pbr->bpb));

	//	Make up the extended BPB

	pbr->exbpb.BootSignature		= 0x29;

	//	use the tick count as the volume serial number
	pbr->exbpb.VolumeSerialNumber	= GetTickCount();

	CopyMemory(pbr->exbpb.VolumeLabel,
		VFD_VOLUME_LABEL, sizeof(pbr->exbpb.VolumeLabel));

	CopyMemory(pbr->exbpb.FileSystemType,
		VFD_FILESYSTEM, sizeof(pbr->exbpb.FileSystemType));

	//	Set the boot record signature

	*(pBuffer + VFD_BYTES_PER_SECTOR - 2) = 0x55;
	*(pBuffer + VFD_BYTES_PER_SECTOR - 1) = 0xaa;

	//
	//	Clear FAT areas
	//
	fat = pBuffer + VFD_SECTOR_TO_BYTE(bpb->ReservedSectors);

	ZeroMemory(
		fat,
		VFD_SECTOR_TO_BYTE(bpb->SectorsPerFAT * bpb->NumberOfFATs));

	//
	//	Make up FAT entries for the root directory
	//
	for (idx = 0; idx < bpb->NumberOfFATs; idx++) {
		*fat = bpb->MediaDescriptor;
		*(fat + 1) = 0xff;
		*(fat + 2) = 0xff;

		fat += VFD_SECTOR_TO_BYTE(bpb->SectorsPerFAT);
	}

	//
	//	Clear root directory entries
	//
	ZeroMemory(fat, bpb->RootEntries * FAT_DIR_ENTRY_SIZE);

	VFDTRACE(0,
		("[VFD] VfdFormatImage - OUT\n"));

	return ERROR_SUCCESS;
}