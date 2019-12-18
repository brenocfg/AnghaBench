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
struct TYPE_6__ {scalar_t__ Id; struct TYPE_6__* Next; } ;
struct TYPE_5__ {TYPE_2__* FirstLine; } ;
typedef  TYPE_1__* PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHELINE ;

/* Variables and functions */

PINFCACHELINE
InfpFindLineById(PINFCACHESECTION Section, UINT Id)
{
    PINFCACHELINE Line;

    for (Line = Section->FirstLine;
         Line != NULL;
         Line = Line->Next)
    {
        if (Line->Id == Id)
        {
            return Line;
        }
    }

    return NULL;
}