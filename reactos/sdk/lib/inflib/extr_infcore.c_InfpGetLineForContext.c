#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Line; } ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  int /*<<< orphan*/ * PINFCACHESECTION ;
typedef  int /*<<< orphan*/ * PINFCACHELINE ;

/* Variables and functions */
 int /*<<< orphan*/ * InfpFindLineById (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InfpGetSectionForContext (TYPE_1__*) ; 

PINFCACHELINE
InfpGetLineForContext(PINFCONTEXT Context)
{
    PINFCACHESECTION Section;

    Section = InfpGetSectionForContext(Context);
    if (Section == NULL)
    {
        return NULL;
    }

    return InfpFindLineById(Section, Context->Line);
}