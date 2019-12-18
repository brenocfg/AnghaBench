#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int SymbolsOffset; int SymbolsLength; int StringsOffset; int StringsLength; } ;
struct TYPE_4__ {int SymbolsCount; int StringsLength; int /*<<< orphan*/  Strings; int /*<<< orphan*/  Symbols; } ;
typedef  int /*<<< orphan*/  ROSSYM_HEADER ;
typedef  int /*<<< orphan*/  ROSSYM_ENTRY ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PROSSYM_INFO ;
typedef  TYPE_2__* PROSSYM_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

VOID
RosSymGetRawData(PROSSYM_INFO RosSymInfo, PVOID RawData)
{
  PROSSYM_HEADER RosSymHeader;

  RosSymHeader = (PROSSYM_HEADER) RawData;
  RosSymHeader->SymbolsOffset = sizeof(ROSSYM_HEADER);
  RosSymHeader->SymbolsLength = RosSymInfo->SymbolsCount * sizeof(ROSSYM_ENTRY);
  RosSymHeader->StringsOffset = RosSymHeader->SymbolsOffset + RosSymHeader->SymbolsLength;
  RosSymHeader->StringsLength = RosSymInfo->StringsLength;

  memcpy((char *) RawData + RosSymHeader->SymbolsOffset, RosSymInfo->Symbols,
         RosSymHeader->SymbolsLength);
  memcpy((char *) RawData + RosSymHeader->StringsOffset, RosSymInfo->Strings,
         RosSymHeader->StringsLength);
}