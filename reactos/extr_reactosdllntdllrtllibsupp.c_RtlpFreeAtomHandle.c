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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  RtlHandleTable; } ;
struct TYPE_5__ {scalar_t__ HandleIndex; } ;
typedef  int /*<<< orphan*/  PRTL_HANDLE_TABLE_ENTRY ;
typedef  TYPE_1__* PRTL_ATOM_TABLE_ENTRY ;
typedef  TYPE_2__* PRTL_ATOM_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  RtlFreeHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RtlIsValidIndexHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VOID
RtlpFreeAtomHandle(PRTL_ATOM_TABLE AtomTable, PRTL_ATOM_TABLE_ENTRY Entry)
{
   PRTL_HANDLE_TABLE_ENTRY RtlHandleEntry;

   if (RtlIsValidIndexHandle(&AtomTable->RtlHandleTable,
                             (ULONG)Entry->HandleIndex,
                             &RtlHandleEntry))
   {
      RtlFreeHandle(&AtomTable->RtlHandleTable,
                    RtlHandleEntry);
   }
}