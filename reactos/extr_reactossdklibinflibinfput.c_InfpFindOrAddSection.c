#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * Section; int /*<<< orphan*/ * Line; int /*<<< orphan*/  Inf; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/  PINFCACHE ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;
typedef  int /*<<< orphan*/  INFCONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  INF_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 int /*<<< orphan*/ * InfpAddSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InfpFindSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* MALLOC (int) ; 

INFSTATUS
InfpFindOrAddSection(PINFCACHE Cache,
                     PCWSTR Section,
                     PINFCONTEXT *Context)
{
  DPRINT("InfpFindOrAddSection section %S\n", Section);

  *Context = MALLOC(sizeof(INFCONTEXT));
  if (NULL == *Context)
    {
      DPRINT1("MALLOC() failed\n");
      return INF_STATUS_NO_MEMORY;
    }

  (*Context)->Inf = Cache;
  (*Context)->Section = InfpFindSection(Cache, Section);
  (*Context)->Line = NULL;
  if (NULL == (*Context)->Section)
    {
      DPRINT("Section not found, creating it\n");
      (*Context)->Section = InfpAddSection(Cache, Section);
      if (NULL == (*Context)->Section)
        {
          DPRINT("Failed to create section\n");
          FREE(*Context);
          return INF_STATUS_NO_MEMORY;
        }
    }

  return INF_STATUS_SUCCESS;
}