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
struct TYPE_3__ {int /*<<< orphan*/ * Line; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 int /*<<< orphan*/ * InfpAddFieldToLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

INFSTATUS
InfpAddField(PINFCONTEXT Context, PCWSTR Data)
{
  if (NULL == Context || NULL == Context->Line)
    {
      DPRINT1("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  if (NULL == InfpAddFieldToLine(Context->Line, Data))
    {
      DPRINT("Failed to add field\n");
      return INF_STATUS_NO_MEMORY;
    }

  return INF_STATUS_SUCCESS;
}