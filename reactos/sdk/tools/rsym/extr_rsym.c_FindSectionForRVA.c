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
struct TYPE_5__ {scalar_t__ VirtualSize; } ;
struct TYPE_6__ {scalar_t__ VirtualAddress; TYPE_1__ Misc; } ;
typedef  TYPE_2__* PIMAGE_SECTION_HEADER ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */

__attribute__((used)) static PIMAGE_SECTION_HEADER
FindSectionForRVA(DWORD RVA, unsigned NumberOfSections, PIMAGE_SECTION_HEADER SectionHeaders)
{
    unsigned Section;

    for (Section = 0; Section < NumberOfSections; Section++)
    {
        if (SectionHeaders[Section].VirtualAddress <= RVA &&
            RVA < SectionHeaders[Section].VirtualAddress + SectionHeaders[Section].Misc.VirtualSize)
        {
            return SectionHeaders + Section;
        }
    }

    return NULL;
}