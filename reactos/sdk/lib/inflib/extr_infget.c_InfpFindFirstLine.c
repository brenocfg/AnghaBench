#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  Id; } ;
struct TYPE_10__ {int /*<<< orphan*/  Id; TYPE_3__* FirstLine; } ;
struct TYPE_9__ {int /*<<< orphan*/  Line; int /*<<< orphan*/  Section; scalar_t__ Inf; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHESECTION ;
typedef  TYPE_3__* PINFCACHELINE ;
typedef  int /*<<< orphan*/ * PINFCACHE ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/  INFSTATUS ;
typedef  int /*<<< orphan*/  INFCONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  INF_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  INF_STATUS_NOT_FOUND ; 
 int /*<<< orphan*/  INF_STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  INF_STATUS_SUCCESS ; 
 TYPE_3__* InfpFindKeyLine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* InfpFindSection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* MALLOC (int) ; 

INFSTATUS
InfpFindFirstLine(PINFCACHE Cache,
                  PCWSTR Section,
                  PCWSTR Key,
                  PINFCONTEXT *Context)
{
  PINFCACHESECTION CacheSection;
  PINFCACHELINE CacheLine;

  if (Cache == NULL || Section == NULL || Context == NULL)
    {
      DPRINT1("Invalid parameter\n");
      return INF_STATUS_INVALID_PARAMETER;
    }

  CacheSection = InfpFindSection(Cache, Section);
  if (NULL == CacheSection)
    {
      DPRINT("Section not found\n");
      return INF_STATUS_NOT_FOUND;
    }

  if (Key != NULL)
    {
      CacheLine = InfpFindKeyLine(CacheSection, Key);
    }
  else
    {
      CacheLine = CacheSection->FirstLine;
    }

  if (NULL == CacheLine)
    {
      DPRINT("Key not found\n");
      return INF_STATUS_NOT_FOUND;
    }

  *Context = MALLOC(sizeof(INFCONTEXT));
  if (NULL == *Context)
    {
      DPRINT1("MALLOC() failed\n");
      return INF_STATUS_NO_MEMORY;
    }
  (*Context)->Inf = (PVOID)Cache;
  (*Context)->Section = CacheSection->Id;
  (*Context)->Line = CacheLine->Id;

  return INF_STATUS_SUCCESS;
}