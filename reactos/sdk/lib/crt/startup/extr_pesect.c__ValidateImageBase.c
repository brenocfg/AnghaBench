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
typedef  int /*<<< orphan*/  WINBOOL ;
struct TYPE_6__ {scalar_t__ e_magic; scalar_t__ e_lfanew; } ;
struct TYPE_5__ {scalar_t__ Signature; int /*<<< orphan*/  OptionalHeader; } ;
struct TYPE_4__ {scalar_t__ Magic; } ;
typedef  TYPE_1__* PIMAGE_OPTIONAL_HEADER ;
typedef  TYPE_2__* PIMAGE_NT_HEADERS ;
typedef  TYPE_3__* PIMAGE_DOS_HEADER ;
typedef  scalar_t__ PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IMAGE_DOS_SIGNATURE ; 
 scalar_t__ IMAGE_NT_OPTIONAL_HDR_MAGIC ; 
 scalar_t__ IMAGE_NT_SIGNATURE ; 
 int /*<<< orphan*/  TRUE ; 

WINBOOL
_ValidateImageBase (PBYTE pImageBase)
{
  PIMAGE_DOS_HEADER pDOSHeader;
  PIMAGE_NT_HEADERS pNTHeader;
  PIMAGE_OPTIONAL_HEADER pOptHeader;

  pDOSHeader = (PIMAGE_DOS_HEADER) pImageBase;
  if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
    return FALSE;
  pNTHeader = (PIMAGE_NT_HEADERS) ((PBYTE) pDOSHeader + pDOSHeader->e_lfanew);
  if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
    return FALSE;
  pOptHeader = (PIMAGE_OPTIONAL_HEADER) &pNTHeader->OptionalHeader;
  if (pOptHeader->Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC)
    return FALSE;
  return TRUE;
}