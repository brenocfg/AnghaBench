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
struct TYPE_3__ {int /*<<< orphan*/ * Line; int /*<<< orphan*/  Section; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 int /*<<< orphan*/ * InfpAddKeyToLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InfpAddLine (int /*<<< orphan*/ ) ; 

INFSTATUS
InfpAddLineWithKey(PINFCONTEXT Context, PCWSTR Key)
{
  if (NULL == Context)
    {
      DPRINT1("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  Context->Line = InfpAddLine(Context->Section);
  if (NULL == Context->Line)
    {
      DPRINT("Failed to create line\n");
      return INF_STATUS_NO_MEMORY;
    }

  if (NULL != Key && NULL == InfpAddKeyToLine(Context->Line, Key))
    {
      DPRINT("Failed to add key\n");
      return INF_STATUS_NO_MEMORY;
    }

  return INF_STATUS_SUCCESS;
}