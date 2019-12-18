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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {struct TYPE_5__* Type; struct TYPE_5__* Name; } ;
struct TYPE_4__ {int NumElements; TYPE_2__* Elements; } ;
typedef  TYPE_1__* PROSSYM_AGGREGATE ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

VOID
RosSymFreeAggregate(PROSSYM_AGGREGATE Aggregate)
{
    int i;
    for (i = 0; i < Aggregate->NumElements; i++) {
        free(Aggregate->Elements[i].Name);
        free(Aggregate->Elements[i].Type);
    }
    free(Aggregate->Elements);
}