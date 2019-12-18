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
struct TYPE_5__ {TYPE_1__* FirstField; int /*<<< orphan*/ * Key; } ;
struct TYPE_4__ {int /*<<< orphan*/ * Data; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/ * PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_2__* InfpGetLineForContext (int /*<<< orphan*/ *) ; 

INFSTATUS
InfpGetData(PINFCONTEXT Context,
            PWCHAR *Key,
            PWCHAR *Data)
{
  PINFCACHELINE CacheKey;

  if (Context == NULL || Data == NULL)
    {
      DPRINT("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  CacheKey = InfpGetLineForContext(Context);
  if (Key != NULL)
    *Key = CacheKey->Key;

  if (Data != NULL)
    {
      if (CacheKey->FirstField == NULL)
        {
          *Data = NULL;
        }
      else
        {
          *Data = CacheKey->FirstField->Data;
        }
    }

  return INF_STATUS_SUCCESS;
}