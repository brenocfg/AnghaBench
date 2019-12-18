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
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {struct TYPE_5__* Next; int /*<<< orphan*/  Data; } ;
struct TYPE_4__ {TYPE_2__* FirstField; scalar_t__ FieldCount; } ;
typedef  scalar_t__* PWSTR ;
typedef  scalar_t__* PWCHAR ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/ * PINFCONTEXT ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  TYPE_2__* PINFCACHEFIELD ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INF_STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_1__* InfpGetLineForContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ ) ; 

INFSTATUS
InfpGetMultiSzField(PINFCONTEXT Context,
                    ULONG FieldIndex,
                    PWSTR ReturnBuffer,
                    ULONG ReturnBufferSize,
                    PULONG RequiredSize)
{
  PINFCACHELINE CacheLine;
  PINFCACHEFIELD CacheField;
  PINFCACHEFIELD FieldPtr;
  ULONG Index;
  ULONG Size;
  PWCHAR Ptr;

  if (Context == NULL || FieldIndex == 0)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  if (RequiredSize != NULL)
    *RequiredSize = 0;

  CacheLine = InfpGetLineForContext(Context);

  if (FieldIndex > (ULONG)CacheLine->FieldCount)
    return INF_STATUS_INVALID_PARAMETER;

  CacheField = CacheLine->FirstField;
  for (Index = 1; Index < FieldIndex; Index++)
    CacheField = CacheField->Next;

  /* Calculate the required buffer size */
  FieldPtr = CacheField;
  Size = 0;
  while (FieldPtr != NULL)
    {
      Size += ((ULONG)strlenW(FieldPtr->Data) + 1);
      FieldPtr = FieldPtr->Next;
    }
  Size++;

  if (RequiredSize != NULL)
    *RequiredSize = Size;

  if (ReturnBuffer != NULL)
    {
      if (ReturnBufferSize < Size)
        return INF_STATUS_BUFFER_OVERFLOW;

      /* Copy multi-sz string */
      Ptr = ReturnBuffer;
      FieldPtr = CacheField;
      while (FieldPtr != NULL)
        {
          Size = (ULONG)strlenW(FieldPtr->Data) + 1;

          strcpyW(Ptr, FieldPtr->Data);

          Ptr = Ptr + Size;
          FieldPtr = FieldPtr->Next;
        }
      *Ptr = 0;
    }

  return INF_STATUS_SUCCESS;
}