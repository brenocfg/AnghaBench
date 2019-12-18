#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {int /*<<< orphan*/  Data; struct TYPE_9__* Next; } ;
struct TYPE_8__ {TYPE_3__* FirstField; int /*<<< orphan*/  Key; scalar_t__ FieldCount; } ;
struct TYPE_7__ {int /*<<< orphan*/  Inf; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  TYPE_3__* PINFCACHEFIELD ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INF_STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_2__* InfpGetLineForContext (TYPE_1__*) ; 
 scalar_t__ InfpSubstituteString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

INFSTATUS
InfpGetStringField(PINFCONTEXT Context,
                   ULONG FieldIndex,
                   PWSTR ReturnBuffer,
                   ULONG ReturnBufferSize,
                   PULONG RequiredSize)
{
  PINFCACHELINE CacheLine;
  PINFCACHEFIELD CacheField;
  ULONG Index;
  PWCHAR Ptr;
  SIZE_T Size;

  if (Context == NULL)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  if (RequiredSize != NULL)
    *RequiredSize = 0;

  CacheLine = InfpGetLineForContext(Context);

  if (FieldIndex > (ULONG)CacheLine->FieldCount)
    return INF_STATUS_INVALID_PARAMETER;

  if (FieldIndex == 0)
    {
      Ptr = CacheLine->Key;
    }
  else
    {
      CacheField = CacheLine->FirstField;
      for (Index = 1; Index < FieldIndex; Index++)
        CacheField = CacheField->Next;

      Ptr = CacheField->Data;
    }

//  Size = (ULONG)strlenW(Ptr) + 1;
  Size = InfpSubstituteString(Context->Inf,
                              Ptr,
                              NULL,
                              0);

  if (RequiredSize != NULL)
    *RequiredSize = (ULONG)Size + 1;

  if (ReturnBuffer != NULL)
    {
      if (ReturnBufferSize <= Size)
        return INF_STATUS_BUFFER_OVERFLOW;

//      strcpyW(ReturnBuffer, Ptr);
      InfpSubstituteString(Context->Inf,
                           Ptr,
                           ReturnBuffer,
                           ReturnBufferSize);
    }

  return INF_STATUS_SUCCESS;
}