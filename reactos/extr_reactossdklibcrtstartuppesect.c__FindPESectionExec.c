#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ e_lfanew; } ;
struct TYPE_8__ {unsigned int NumberOfSections; } ;
struct TYPE_10__ {TYPE_1__ FileHeader; } ;
struct TYPE_9__ {int Characteristics; } ;
typedef  TYPE_2__* PIMAGE_SECTION_HEADER ;
typedef  TYPE_3__* PIMAGE_NT_HEADERS ;
typedef  TYPE_4__* PIMAGE_DOS_HEADER ;
typedef  scalar_t__ PBYTE ;

/* Variables and functions */
 TYPE_2__* IMAGE_FIRST_SECTION (TYPE_3__*) ; 
 int IMAGE_SCN_MEM_EXECUTE ; 
 int /*<<< orphan*/  _ValidateImageBase (scalar_t__) ; 
 int /*<<< orphan*/  __ImageBase ; 

PIMAGE_SECTION_HEADER
_FindPESectionExec (size_t eNo)
{
  PBYTE pImageBase;
  PIMAGE_NT_HEADERS pNTHeader;
  PIMAGE_SECTION_HEADER pSection;
  unsigned int iSection;

  pImageBase = (PBYTE) &__ImageBase;
  if (! _ValidateImageBase (pImageBase))
    return NULL;

  pNTHeader = (PIMAGE_NT_HEADERS) (pImageBase + ((PIMAGE_DOS_HEADER) pImageBase)->e_lfanew);

  for (iSection = 0, pSection = IMAGE_FIRST_SECTION (pNTHeader);
    iSection < pNTHeader->FileHeader.NumberOfSections;
    ++iSection,++pSection)
    {
      if ((pSection->Characteristics & IMAGE_SCN_MEM_EXECUTE) != 0)
      {
	if (!eNo)
	  return pSection;
	--eNo;
      }
    }
  return NULL;
}