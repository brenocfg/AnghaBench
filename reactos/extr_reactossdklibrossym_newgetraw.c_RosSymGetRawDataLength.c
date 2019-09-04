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
typedef  scalar_t__ ULONG ;
struct TYPE_3__ {int SymbolsCount; scalar_t__ StringsLength; } ;
typedef  int /*<<< orphan*/  ROSSYM_HEADER ;
typedef  int /*<<< orphan*/  ROSSYM_ENTRY ;
typedef  TYPE_1__* PROSSYM_INFO ;

/* Variables and functions */

ULONG
RosSymGetRawDataLength(PROSSYM_INFO RosSymInfo)
{
  return sizeof(ROSSYM_HEADER)
         + RosSymInfo->SymbolsCount * sizeof(ROSSYM_ENTRY)
         + RosSymInfo->StringsLength;
}