#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* USHORT ;
typedef  int ULONG ;
struct TYPE_7__ {void* Flags; } ;
struct TYPE_10__ {TYPE_1__ Handle; TYPE_2__* AtomEntry; } ;
struct TYPE_9__ {int /*<<< orphan*/  RtlHandleTable; } ;
struct TYPE_8__ {void* Atom; void* HandleIndex; } ;
typedef  int /*<<< orphan*/ * PRTL_HANDLE_TABLE_ENTRY ;
typedef  TYPE_2__* PRTL_ATOM_TABLE_ENTRY ;
typedef  TYPE_3__* PRTL_ATOM_TABLE ;
typedef  TYPE_4__* PRTL_ATOM_HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* RTL_HANDLE_VALID ; 
 int /*<<< orphan*/ * RtlAllocateHandle (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  RtlFreeHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
RtlpCreateAtomHandle(PRTL_ATOM_TABLE AtomTable, PRTL_ATOM_TABLE_ENTRY Entry)
{
   ULONG HandleIndex;
   PRTL_HANDLE_TABLE_ENTRY RtlHandle;

   RtlHandle = RtlAllocateHandle(&AtomTable->RtlHandleTable,
                                 &HandleIndex);
   if (RtlHandle != NULL)
   {
      PRTL_ATOM_HANDLE AtomHandle = (PRTL_ATOM_HANDLE)RtlHandle;

      /* FIXME - Handle Indexes >= 0xC000 ?! */
      if (HandleIndex < 0xC000)
      {
         Entry->HandleIndex = (USHORT)HandleIndex;
         Entry->Atom = 0xC000 + (USHORT)HandleIndex;

         AtomHandle->AtomEntry = Entry;
         AtomHandle->Handle.Flags = RTL_HANDLE_VALID;

         return TRUE;
      }
      else
      {
         /* set the valid flag, otherwise RtlFreeHandle will fail! */
         AtomHandle->Handle.Flags = RTL_HANDLE_VALID;

         RtlFreeHandle(&AtomTable->RtlHandleTable,
                       RtlHandle);
      }
   }

   return FALSE;
}