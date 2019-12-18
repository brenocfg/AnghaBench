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
typedef  scalar_t__ UCHAR ;
struct TYPE_5__ {struct TYPE_5__* Next; int /*<<< orphan*/  Data; } ;
struct TYPE_4__ {scalar_t__ FieldCount; TYPE_2__* FirstField; } ;
typedef  scalar_t__* PULONG ;
typedef  scalar_t__* PUCHAR ;
typedef  int /*<<< orphan*/ * PINFCONTEXT ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  TYPE_2__* PINFCACHEFIELD ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INF_STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_1__* InfpGetLineForContext (int /*<<< orphan*/ *) ; 
 scalar_t__ strtoulW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

INFSTATUS
InfpGetBinaryField(PINFCONTEXT Context,
                   ULONG FieldIndex,
                   PUCHAR ReturnBuffer,
                   ULONG ReturnBufferSize,
                   PULONG RequiredSize)
{
  PINFCACHELINE CacheLine;
  PINFCACHEFIELD CacheField;
  ULONG Index;
  ULONG Size;
  PUCHAR Ptr;

  if (Context == NULL || FieldIndex == 0)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  if (RequiredSize != NULL)
    *RequiredSize = 0;

  CacheLine = InfpGetLineForContext(Context);

  if (FieldIndex > (ULONG)CacheLine->FieldCount)
    return INF_STATUS_NOT_FOUND;

  CacheField = CacheLine->FirstField;
  for (Index = 1; Index < FieldIndex; Index++)
    CacheField = CacheField->Next;

  Size = (ULONG)CacheLine->FieldCount - FieldIndex + 1;

  if (RequiredSize != NULL)
    *RequiredSize = Size;

  if (ReturnBuffer != NULL)
    {
      if (ReturnBufferSize < Size)
        return INF_STATUS_BUFFER_OVERFLOW;

      /* Copy binary data */
      Ptr = ReturnBuffer;
      while (CacheField != NULL)
        {
          *Ptr = (UCHAR)strtoulW(CacheField->Data, NULL, 16);

          Ptr++;
          CacheField = CacheField->Next;
        }
    }

  return INF_STATUS_SUCCESS;
}