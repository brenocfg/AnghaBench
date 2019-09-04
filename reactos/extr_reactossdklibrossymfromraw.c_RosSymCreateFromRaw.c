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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_6__ {int SymbolsOffset; scalar_t__ StringsOffset; scalar_t__ SymbolsLength; int StringsLength; } ;
struct TYPE_5__ {char* Symbols; int SymbolsCount; char* Strings; int StringsLength; } ;
typedef  int /*<<< orphan*/  ROSSYM_INFO ;
typedef  int /*<<< orphan*/  ROSSYM_HEADER ;
typedef  int /*<<< orphan*/  ROSSYM_ENTRY ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PROSSYM_INFO ;
typedef  TYPE_2__* PROSSYM_HEADER ;
typedef  char* PROSSYM_ENTRY ;
typedef  char* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* RosSymAllocMem (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

BOOLEAN
RosSymCreateFromRaw(PVOID RawData, ULONG_PTR DataSize, PROSSYM_INFO *RosSymInfo)
{
  PROSSYM_HEADER RosSymHeader;

  RosSymHeader = (PROSSYM_HEADER) RawData;
  if (RosSymHeader->SymbolsOffset < sizeof(ROSSYM_HEADER)
      || RosSymHeader->StringsOffset < RosSymHeader->SymbolsOffset + RosSymHeader->SymbolsLength
      || DataSize < RosSymHeader->StringsOffset + RosSymHeader->StringsLength
      || 0 != (RosSymHeader->SymbolsLength % sizeof(ROSSYM_ENTRY)))
    {
      DPRINT1("Invalid ROSSYM_HEADER\n");
      return FALSE;
    }

  /* Copy */
  *RosSymInfo = RosSymAllocMem(sizeof(ROSSYM_INFO) + RosSymHeader->SymbolsLength
                               + RosSymHeader->StringsLength + 1);
  if (NULL == *RosSymInfo)
    {
      DPRINT1("Failed to allocate memory for rossym\n");
      return FALSE;
    }
  (*RosSymInfo)->Symbols = (PROSSYM_ENTRY)((char *) *RosSymInfo + sizeof(ROSSYM_INFO));
  (*RosSymInfo)->SymbolsCount = RosSymHeader->SymbolsLength / sizeof(ROSSYM_ENTRY);
  (*RosSymInfo)->Strings = (PCHAR) *RosSymInfo + sizeof(ROSSYM_INFO) + RosSymHeader->SymbolsLength;
  (*RosSymInfo)->StringsLength = RosSymHeader->StringsLength;
  memcpy((*RosSymInfo)->Symbols, (char *) RosSymHeader + RosSymHeader->SymbolsOffset,
         RosSymHeader->SymbolsLength);
  memcpy((*RosSymInfo)->Strings, (char *) RosSymHeader + RosSymHeader->StringsOffset,
         RosSymHeader->StringsLength);
  /* Make sure the last string is null terminated, we allocated an extra byte for that */
  (*RosSymInfo)->Strings[(*RosSymInfo)->StringsLength] = '\0';

  return TRUE;
}