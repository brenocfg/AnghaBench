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
struct TYPE_3__ {int /*<<< orphan*/  Section; scalar_t__ Inf; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/ * PINFCACHESECTION ;
typedef  int /*<<< orphan*/ * PINFCACHE ;

/* Variables and functions */
 int /*<<< orphan*/ * InfpFindSectionById (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PINFCACHESECTION
InfpGetSectionForContext(PINFCONTEXT Context)
{
    PINFCACHE Cache;

    if (Context == NULL)
    {
        return NULL;
    }

    Cache = (PINFCACHE)Context->Inf;
    if (Cache == NULL)
    {
        return NULL;
    }

    return InfpFindSectionById(Cache, Context->Section);
}