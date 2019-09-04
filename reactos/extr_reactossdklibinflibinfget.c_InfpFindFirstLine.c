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
struct TYPE_8__ {int /*<<< orphan*/ * FirstLine; } ;
struct TYPE_7__ {void* Line; void* Section; void* Inf; } ;
typedef  void* PVOID ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHESECTION ;
typedef  int /*<<< orphan*/ * PINFCACHELINE ;
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
 int /*<<< orphan*/ * InfpFindKeyLine (TYPE_2__*,int /*<<< orphan*/ *) ; 
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
  (*Context)->Section = (PVOID)CacheSection;
  (*Context)->Line = (PVOID)CacheLine;

  return INF_STATUS_SUCCESS;
}