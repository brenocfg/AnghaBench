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
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  Data; struct TYPE_5__* Next; } ;
struct TYPE_4__ {TYPE_2__* FirstField; int /*<<< orphan*/  Key; scalar_t__ FieldCount; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/ * PINFCONTEXT ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  TYPE_2__* PINFCACHEFIELD ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_1__* InfpGetLineForContext (int /*<<< orphan*/ *) ; 
 scalar_t__ strtolW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

INFSTATUS
InfpGetIntField(PINFCONTEXT Context,
                ULONG FieldIndex,
                INT *IntegerValue)
{
  PINFCACHELINE CacheLine;
  PINFCACHEFIELD CacheField;
  ULONG Index;
  PWCHAR Ptr;

  if (Context == NULL || IntegerValue == NULL)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  CacheLine = InfpGetLineForContext(Context);

  if (FieldIndex > (ULONG)CacheLine->FieldCount)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

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

  *IntegerValue = (LONG)strtolW(Ptr, NULL, 0);

  return INF_STATUS_SUCCESS;
}