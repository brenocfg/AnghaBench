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
typedef  int WINBOOL ;
struct TYPE_3__ {int Characteristics; } ;
typedef  TYPE_1__* PIMAGE_SECTION_HEADER ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int FALSE ; 
 int IMAGE_SCN_MEM_WRITE ; 
 TYPE_1__* _FindPESection (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _ValidateImageBase (scalar_t__) ; 
 int /*<<< orphan*/  __ImageBase ; 

WINBOOL
_IsNonwritableInCurrentImage (PBYTE pTarget)
{
  PBYTE pImageBase;
  DWORD_PTR rvaTarget;
  PIMAGE_SECTION_HEADER pSection;

  pImageBase = (PBYTE) &__ImageBase;
  if (! _ValidateImageBase (pImageBase))
    return FALSE;
  rvaTarget = pTarget - pImageBase;
  pSection = _FindPESection (pImageBase, rvaTarget);
  if (pSection == NULL)
    return FALSE;
  return (pSection->Characteristics & IMAGE_SCN_MEM_WRITE) == 0;
}