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
typedef  scalar_t__ UINT ;
struct TYPE_6__ {TYPE_1__* FirstSection; } ;
struct TYPE_5__ {scalar_t__ Id; struct TYPE_5__* Next; } ;
typedef  TYPE_1__* PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHE ;

/* Variables and functions */

PINFCACHESECTION
InfpFindSectionById(PINFCACHE Cache, UINT Id)
{
    PINFCACHESECTION Section;

    for (Section = Cache->FirstSection;
         Section != NULL;
         Section = Section->Next)
    {
        if (Section->Id == Id)
        {
            return Section;
        }
    }

    return NULL;
}