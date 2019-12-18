#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* Next; } ;
struct TYPE_9__ {int /*<<< orphan*/  Line; int /*<<< orphan*/  Section; int /*<<< orphan*/  Inf; } ;
struct TYPE_8__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__* PINFCONTEXT ;
typedef  TYPE_3__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_3__* InfpGetLineForContext (TYPE_2__*) ; 

INFSTATUS
InfpFindNextLine(PINFCONTEXT ContextIn,
                 PINFCONTEXT ContextOut)
{
  PINFCACHELINE CacheLine;

  if (ContextIn == NULL || ContextOut == NULL)
    return INF_STATUS_INVALID_PARAMETER;

  CacheLine = InfpGetLineForContext(ContextIn);
  if (CacheLine == NULL)
    return INF_STATUS_INVALID_PARAMETER;

  if (CacheLine->Next == NULL)
    return INF_STATUS_NOT_FOUND;

  if (ContextIn != ContextOut)
    {
      ContextOut->Inf = ContextIn->Inf;
      ContextOut->Section = ContextIn->Section;
    }
  ContextOut->Line = CacheLine->Next->Id;

  return INF_STATUS_SUCCESS;
}