#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Id; } ;
struct TYPE_7__ {int /*<<< orphan*/  Line; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/  PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 int /*<<< orphan*/ * InfpAddKeyToLine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* InfpAddLine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpGetSectionForContext (TYPE_1__*) ; 

INFSTATUS
InfpAddLineWithKey(PINFCONTEXT Context, PCWSTR Key)
{
  PINFCACHESECTION Section;
  PINFCACHELINE Line;

  if (NULL == Context)
    {
      DPRINT1("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  Section = InfpGetSectionForContext(Context);
  Line = InfpAddLine(Section);
  if (NULL == Line)
    {
      DPRINT("Failed to create line\n");
      return INF_STATUS_NO_MEMORY;
    }
  Context->Line = Line->Id;

  if (NULL != Key && NULL == InfpAddKeyToLine(Line, Key))
    {
      DPRINT("Failed to add key\n");
      return INF_STATUS_NO_MEMORY;
    }

  return INF_STATUS_SUCCESS;
}