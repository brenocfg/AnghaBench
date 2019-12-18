#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* Next; int /*<<< orphan*/  Id; int /*<<< orphan*/ * Key; } ;
struct TYPE_8__ {int /*<<< orphan*/  Line; int /*<<< orphan*/  Section; int /*<<< orphan*/  Inf; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/ * PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  scalar_t__* PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_2__* InfpGetLineForContext (TYPE_1__*) ; 
 int /*<<< orphan*/ * InfpGetSectionForContext (TYPE_1__*) ; 
 scalar_t__ strcmpiW (int /*<<< orphan*/ *,scalar_t__*) ; 

INFSTATUS
InfpFindNextMatchLine(PINFCONTEXT ContextIn,
                      PCWSTR Key,
                      PINFCONTEXT ContextOut)
{
  PINFCACHESECTION Section;
  PINFCACHELINE CacheLine;

  if (ContextIn == NULL || ContextOut == NULL || Key == NULL || *Key == 0)
    return INF_STATUS_INVALID_PARAMETER;

  Section = InfpGetSectionForContext(ContextIn);
  if (Section == NULL)
      return INF_STATUS_INVALID_PARAMETER;

  CacheLine = InfpGetLineForContext(ContextIn);
  while (CacheLine != NULL)
    {
      if (CacheLine->Key != NULL && strcmpiW (CacheLine->Key, Key) == 0)
        {

          if (ContextIn != ContextOut)
            {
              ContextOut->Inf = ContextIn->Inf;
              ContextOut->Section = ContextIn->Section;
            }
          ContextOut->Line = CacheLine->Id;

          return INF_STATUS_SUCCESS;
        }

      CacheLine = CacheLine->Next;
    }

  return INF_STATUS_NOT_FOUND;
}