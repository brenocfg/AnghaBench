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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ Reserved; scalar_t__ CodePage; int /*<<< orphan*/  Size; scalar_t__ OffsetToData; } ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PIMAGE_RESOURCE_DATA_ENTRY ;

/* Variables and functions */

__attribute__((used)) static
VOID
InitializeDataEntry(
    PVOID ImageBase,
    PIMAGE_RESOURCE_DATA_ENTRY DataEntry,
    PVOID Data,
    ULONG Size)
{

    DataEntry->OffsetToData = (PUCHAR)Data - (PUCHAR)ImageBase;
    DataEntry->Size = Size;
    DataEntry->CodePage = 0;
    DataEntry->Reserved = 0;
}