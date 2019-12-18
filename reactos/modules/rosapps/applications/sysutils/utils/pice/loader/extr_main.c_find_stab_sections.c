#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int PointerToRawData; int SizeOfRawData; int /*<<< orphan*/  Name; } ;
typedef  int PSTAB_ENTRY ;
typedef  TYPE_1__* PIMAGE_SECTION_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void find_stab_sections(void* p,PIMAGE_SECTION_HEADER section, unsigned cSections,
							  PSTAB_ENTRY* ppStab,int* pLen,char** ppStr,int* pnStabStrLen)
{
	unsigned i;
    //printf("LOADER: enter find_stab_sections()\n");
    *ppStab = 0;
    *ppStr = 0;

	for ( i=1; i <= cSections; i++, section++ )
    {

		if(strcmp(section->Name,".stab") == 0)
        {
            *ppStab = (PSTAB_ENTRY)((int)p + section->PointerToRawData);
            *pLen = section->SizeOfRawData;
            printf("LOADER: .stab @ %x (offset %x) len = %x\n",*ppStab,section->PointerToRawData,section->SizeOfRawData);
        }
        else if(strncmp(section->Name,".stabstr",strlen(".stabstr")) == 0)
        {
            *ppStr = (char*)((int)p + section->PointerToRawData);
			*pnStabStrLen = section->SizeOfRawData;
            printf("LOADER: .stabstr @ %x (offset %x) len = %x\n",*ppStab,section->PointerToRawData,section->SizeOfRawData);
        }
    }

    //printf("LOADER: leave find_stab_sections()\n");
}