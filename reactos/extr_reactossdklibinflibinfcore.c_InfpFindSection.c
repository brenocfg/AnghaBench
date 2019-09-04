#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* FirstSection; } ;
struct TYPE_5__ {struct TYPE_5__* Next; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__* PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHE ;
typedef  int /*<<< orphan*/ * PCWSTR ;

/* Variables and functions */
 scalar_t__ strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

PINFCACHESECTION
InfpFindSection(PINFCACHE Cache,
                PCWSTR Name)
{
  PINFCACHESECTION Section = NULL;

  if (Cache == NULL || Name == NULL)
    {
      return NULL;
    }

  /* iterate through list of sections */
  Section = Cache->FirstSection;
  while (Section != NULL)
    {
      if (strcmpiW(Section->Name, Name) == 0)
        {
          return Section;
        }

      /* get the next section*/
      Section = Section->Next;
    }

  return NULL;
}