#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ e_lfanew; } ;
struct TYPE_4__ {scalar_t__ NumberOfSections; } ;
struct TYPE_5__ {TYPE_1__ FileHeader; } ;
typedef  TYPE_2__* PIMAGE_NT_HEADERS ;
typedef  TYPE_3__* PIMAGE_DOS_HEADER ;
typedef  scalar_t__ PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  _ValidateImageBase (scalar_t__) ; 
 int /*<<< orphan*/  __ImageBase ; 

int
__mingw_GetSectionCount (void)
{
  PBYTE pImageBase;
  PIMAGE_NT_HEADERS pNTHeader;

  pImageBase = (PBYTE) &__ImageBase;
  if (! _ValidateImageBase (pImageBase))
    return 0;

  pNTHeader = (PIMAGE_NT_HEADERS) (pImageBase + ((PIMAGE_DOS_HEADER) pImageBase)->e_lfanew);

  return (int) pNTHeader->FileHeader.NumberOfSections;
}