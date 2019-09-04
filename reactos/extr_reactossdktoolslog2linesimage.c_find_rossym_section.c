#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t NumberOfSections; } ;
struct TYPE_6__ {scalar_t__ Name; } ;
typedef  TYPE_1__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_2__* PIMAGE_FILE_HEADER ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PIMAGE_SECTION_HEADER
find_rossym_section(PIMAGE_FILE_HEADER PEFileHeader, PIMAGE_SECTION_HEADER PESectionHeaders)
{
    size_t i;
    for (i = 0; i < PEFileHeader->NumberOfSections; i++)
    {
        if (0 == strcmp((char *)PESectionHeaders[i].Name, ".rossym"))
            return &PESectionHeaders[i];
    }
    return NULL;
}