#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct _IMAGE_SECTION_HEADER {scalar_t__ PointerToRawData; scalar_t__ VirtualAddress; scalar_t__ SizeOfRawData; } ;
struct TYPE_2__ {int /*<<< orphan*/  Buffer; } ;

/* Variables and functions */
 TYPE_1__* ANSI_NAME_STRING (struct _IMAGE_SECTION_HEADER*) ; 
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,...) ; 
 scalar_t__ nil ; 

ulong pefindrva(struct _IMAGE_SECTION_HEADER *SectionHeaders, int NumberOfSections, ulong TargetPhysical) {
	int i;
	DPRINT("Finding RVA for Physical %x\n", TargetPhysical);
	for (i = 0; i < NumberOfSections; i++) {
		DPRINT("Section %d name %s Raw %x Virt %x\n",
			   i, 
			   ANSI_NAME_STRING(&SectionHeaders[i])->Buffer, 
			   SectionHeaders[i].PointerToRawData,
			   SectionHeaders[i].VirtualAddress);
		if (TargetPhysical >= SectionHeaders[i].PointerToRawData && 
			TargetPhysical < SectionHeaders[i].PointerToRawData + SectionHeaders[i].SizeOfRawData) {
			DPRINT("RVA %x\n", TargetPhysical - SectionHeaders[i].PointerToRawData + SectionHeaders[i].VirtualAddress);
			return TargetPhysical - SectionHeaders[i].PointerToRawData + SectionHeaders[i].VirtualAddress;
		}
	}
	return nil;
}